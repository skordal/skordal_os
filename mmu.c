// SkordalOS MMU Functions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "mmu.h"
#include "mm.h"

// Flag indicating if the MMU has been enabled or not:
bool mmu_enabled = false;

// The kernel first-level descriptor table:
static uint32_t __attribute((aligned(16*1024))) kernel_descriptor_table[4096];

// The bitmap of free pages, where 0 indicates free and 1 indicates used:
static uint32_t * page_bitmap = NULL;

// The position of the next free page in the page bitmap:
static struct {
	int word_index;
	int bit_index;
} next_page_index = {0, 0};

// The total number of pages available:
static int total_pages = 0;
// The total number of free pages available:
static int free_pages = 0;

// Creates a page table entry:
inline uint32_t mmu_create_pt_entry(void * physical_address, mmu_mode_t mode,
	mmu_perm_t permissions);

// Initializes the MMU control registers:
void mmu_init()
{
	// Set up the MMU registers:
	asm volatile(
		// Clear TLB cache:
		"mov v1, #0\n\t"
		"mcr p15, 0, v1, c8, c7, 0\n\t"
		// Set up the TTBCR register, with N = 1:
		"mov v1, #1\n\t"
		"mcr p15, 0, v1, c2, c0, 2\n\t"
		// Load the TTBR1 (OS translation table pointer) register:
		"ldr v2, =kernel_descriptor_table\n\t"
		"orr v2, #(0b10 << 3)|0b11\n\t"
		"mcr p15, 0, v2, c2, c0, 1\n\t"
		// Set domain permissions:
		"ldr v1, =0x55555555\n\t"
		"mcr p15, 0, v1, c3, c0, 0\n\t"
		// Invalidate TLB cache again:
		"mov v1, #0\n\t"
		"mcr p15, 0, v1, c8, c7, 0\n\t"
		:
		:
		: "v1", "v2", "cc"
	);
}

// Sets the current TTBR0 and CONTEXTIDR registers:
void mmu_set_ttbr0(void * new_table, pid_t asid)
{
#ifdef DEBUG_MMU
	debug_print_string("[mmu_set_ttbr0] changing context to ASID ");
	debug_print_dec(asid);
	debug_print_string(" with translation table @ ");
	debug_print_hex(new_table);
	debug_print_newline();
#endif

	asm volatile(
		// Set TTBCR.PD0 to 1:
		"mrc p15, 0, v1, c2, c0, 2\n\t"
		"orr v1, #(1 << 4)\n\t"
		"mcr p15, 0, v1, c2, c0, 2\n\t"
		"isb\n\t"
		// Change CONTEXTIDR:
		"mov v1, %[asid], lsl #8\n\t"
		"orr v1, %[asid]\n\t"
		"mcr p15, 0, v1, c13, c0, 1\n\t"
		// Change the TTBR0 register:
		"orr %[descriptor_table], #(0b10 << 3)|0b11\n\t"
		"mcr p15, 0, %[descriptor_table], c2, c0, 0\n\t"
		// Set TTBCR.PD0 back to 0:
		"isb\n\t"
		"mrc p15, 0, v1, c2, c0, 2\n\t"
		"mvn v2, #(1 << 4)\n\t"
		"and v1, v1, v2\n\t"
		"mcr p15, 0, v1, c2, c0, 2\n\t"
		:
		: [asid] "r" (asid), [descriptor_table] "r" (new_table)
		: "v1", "v2", "cc"
	);
}

// Clears the TLB:
void mmu_clear_tlb()
{
	asm volatile(
		"mov r0, #0\n\t"
		"mcr p15, 0, r0, c8, c7, 0\n\t"	
		:
		:
		: "r0"
	);
}

// Maps the specified physical memory interval to the corresponding interval
// of virtual memory starting at virtual_address with the specified mode
// and permissions:
void mmu_map_interval(void * start_address, void * end_address, void * virtual_address,
	mmu_mode_t mode, mmu_perm_t permissions, uint32_t * descriptor_table)
{
	bool global = descriptor_table == NULL;

#ifdef DEBUG_MMU
	debug_print_string("[mmu_map_interval] mapping interval ");
	debug_print_hex((uint32_t) start_address);
	debug_print_char('-');
	debug_print_hex((uint32_t) end_address);
	debug_print_string(" to ");
	debug_print_hex((uint32_t) virtual_address);
	debug_print_newline();

	if(!global)
	{
		debug_print_string("[mmu_map_interval] mapping non global interval");
		debug_print_newline();
	}
#endif

	uint32_t interval_size = UNSIGNED_DIFF(end_address, start_address);
	if(descriptor_table == NULL)
		descriptor_table = kernel_descriptor_table;

	void * physical = start_address;
	for(void * virtual = virtual_address; virtual < (virtual_address + interval_size);
		virtual += 4096, physical += 4096)
	{
		// Calculate the offset of the virtual address into the first-level translation
		// table:
		int l1_index = (uint32_t) virtual >> 20;

		// Get the existing entry for the virtual address:
		uint32_t table_entry = descriptor_table[l1_index];
		uint32_t * page_table;
		// If there is an existing page table, load it:
		if(table_entry & MMU_L1_TYPE_PAGE_TABLE)
		{
			page_table = (uint32_t *) (table_entry & MMU_L1_PAGE_TABLE_ADDRESS_MASK);
#ifdef DEBUG_MMU
			debug_print_string("[mmu_map_interval] page table found @ ");
			debug_print_hex((uint32_t) page_table);
			debug_print_newline();
#endif
		} else { // Otherwise, create a new page table:
			page_table = mm_alloc(1024, 1024);
			zero_mem_4(page_table, 1024);

			table_entry = (uint32_t) page_table | MMU_L1_TYPE_PAGE_TABLE;
			if(global)
				descriptor_table[l1_index] = table_entry;
			else
				descriptor_table[l1_index] = table_entry | MMU_L2_SP_nG;
#ifdef DEBUG_MMU
			debug_print_string("[mmu_map_interval] creating page table @ ");
			debug_print_hex((uint32_t) page_table);
			debug_print_newline();
#endif
		}

		// Calculate the offset of the virtual address into the page table:
		int l2_index = MMU_GET_L2_INDEX((uint32_t) virtual);
		page_table[l2_index] = mmu_create_pt_entry(physical, mode, permissions);
		// Mark the page as used, if it is in RAM:
		if((uint32_t) physical & 0x80000000)
			mmu_mark_as_used(physical);
	}
}

// Unmaps an interval of virtual memory and frees its page tables:
void mmu_unmap_interval(void * start_address, void * end_address, uint32_t * descriptor_table)
{
	// TODO: Write me :-)
}

// Creates a page table entry from the arguments:
inline uint32_t mmu_create_pt_entry(void * physical_address, mmu_mode_t mode, 
	mmu_perm_t permissions)
{
	uint32_t retval = MMU_L2_TYPE_SMALL_PAGE|(int) physical_address;

	switch(mode)
	{
		case MMU_MODE_DEVICE:
			retval |= MMU_L2_SP_XN|MMU_L2_SP_S|MMU_L2_SP_B;
			break;
		case MMU_MODE_DATA:
			retval |= MMU_L2_SP_XN|MMU_L2_SP_TEX2|MMU_L2_SP_TEX1|MMU_L2_SP_B|MMU_L2_SP_S;
			break;
		case MMU_MODE_STACK:
			retval |= MMU_L2_SP_XN|MMU_L2_SP_TEX2|MMU_L2_SP_TEX0|MMU_L2_SP_B|MMU_L2_SP_S;
			break;
		case MMU_MODE_CODE:
			retval |= MMU_L2_SP_TEX2|MMU_L2_SP_TEX1|MMU_L2_SP_C|MMU_L2_SP_S;
			break;
#ifdef DEBUG_MMU
		default:
			debug_print_string("[mmu_map_interval] ERROR: unrecognized mode: ");
			debug_print_hex(mode);
			debug_print_newline();
#endif
	}

	switch(permissions)
	{
		case MMU_PERM_RW_RW:
			retval |= MMU_L2_SP_AP1|MMU_L2_SP_AP0;
			break;
		case MMU_PERM_RW_RO:
			retval |= MMU_L2_SP_AP1;
			break;
		case MMU_PERM_RW_NONE:
			retval |= MMU_L2_SP_AP0;
			break;
		case MMU_PERM_RO_RO:
			retval |= MMU_L2_SP_AP2|MMU_L2_SP_AP1|MMU_L2_SP_AP0;
			break;
		case MMU_PERM_RO_NONE:
			retval |= MMU_L2_SP_AP2|MMU_L2_SP_AP0;
		case MMU_PERM_NONE_NONE:
			break;	// Set no AP bits causing no access whatsoever.
#ifdef DEBUG_MMU
		default:
			debug_print_string("[mmu_map_interval] ERROR: unrecognized permissions: ");
			debug_print_hex(permissions);
			debug_print_newline();
#endif
	}

#ifdef DEBUG_PAGETABLE
	debug_print_string("[mmu_create_pt_entry] page table entry created: ");
	debug_print_bitfield(retval);
	debug_print_newline();
#endif

	return retval;
}

// Initializes the bitmap of free pages:
void mmu_init_bitmap()
{
	size_t bitmap_size = ramsize >> 19;

	page_bitmap = mm_alloc(bitmap_size, 4);
	zero_mem_4(page_bitmap, bitmap_size);

	total_pages = ramsize >> 12;
	free_pages = total_pages;
}

void * mmu_get_free_page()
{
	if(free_pages == 0)
		return NULL;
	else {
		uint32_t retval_address = 0x80000000;
		retval_address += next_page_index.word_index << 17;
		retval_address += next_page_index.bit_index << 12;

#ifdef DEBUG_MMU
		debug_print_string("[mmu_get_free_page] free page found @ ");
		debug_print_hex(retval_address);
		debug_print_newline();
#endif

		return (void *) retval_address;
	}
}

// Marks a page as used in the page bitmap:
void mmu_mark_as_used(void * page_address)
{
	uint32_t word_index = ((uint32_t) page_address & ~0x80000000) >> 17;
	uint32_t bit_index = (((uint32_t) page_address & ~0x80000000) & ~mask_left(1 << 17)) >> 12;

	page_bitmap[word_index] |= (1 << bit_index);
	mmu_find_next_index();
	--free_pages;
}

// Marks a page as unused in the page bitmap:
void mmu_mark_as_unused(void * page_address)
{
	uint32_t word_index = ((uint32_t) page_address & ~0x80000000) >> 17;
	uint32_t bit_index = (((uint32_t) page_address & ~0x80000000) & ~mask_left(1 << 17)) >> 12;

	page_bitmap[word_index] &= ~(1 << bit_index);
	++free_pages;
}

// Finds the next free page in the page bitmap and stores the index of it:
void mmu_find_next_index()
{
	for(int i = 0; i < (ramsize >> 19); ++i)
	{
		uint32_t temp = page_bitmap[i];
		for(int b = 0; b < 32; ++b)
		{
			if(((temp >> b) & 1) == 0)
			{
				next_page_index.word_index = i;
				next_page_index.bit_index = b;
#ifdef DEBUG_MMU
				debug_print_string("[mmu_find_next_index] next free page @ ");
				debug_print_dec(i);
				debug_print_char(':');
				debug_print_dec(b);
				debug_print_newline();
#endif
				return;
			}
		}
	}
}

