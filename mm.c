// SkordalOS Memory Manager Functions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "mm.h"

// Stores the size of RAM in bytes:
uint32_t ramsize = 0;

// Symbols from the linker scripts:
extern void * text_start, * text_end;
extern void * data_start, *data_end, * data_page_end;
extern void * stack_top, * stack_bottom;
extern void * kernel_stack_top;

// Used for initializing the memory manager:
static void * kernel_end = &data_end;

// Kernel memory managed dataspace start:
static void * dataspace_start;
// Kernel dataspace end:
static void * dataspace_end;
// Pointer to the first mm_blk_info_t structure in memory:
static mm_blk_info_t * first_block = NULL;

// Initializes the kernel memory manager:
void mm_init()
{
	volatile uint32_t * sdrc_mcfg_cs0 = REG_ADDR(SDRC_BASE, SDRC_MCFG_CS0);
	volatile uint32_t * sdrc_mcfg_cs1 = REG_ADDR(SDRC_BASE, SDRC_MCFG_CS1);

	debug_print_string("Initializing kernel memory manager:");
	debug_print_newline();

	uint32_t revision = *((volatile uint32_t *) REG_ADDR(SDRC_BASE, SDRC_REVISION));
	debug_print_string("\tSDRC revision: ");
	debug_print_dec(IP_REV_MAJOR(revision));
	debug_print_char('.');
	debug_print_dec(IP_REV_MINOR(revision));
	debug_print_newline();

	// Find the size of RAM:	
	ramsize  = SDRC_EXTRACT_RAMSIZE(*sdrc_mcfg_cs0) << 1;
	ramsize += SDRC_EXTRACT_RAMSIZE(*sdrc_mcfg_cs1) << 1;

	debug_print_string("\tRAM detected: ");
	debug_print_dec(ramsize);
	debug_print_string(" Mb");
	debug_print_newline();

	// Convert ramsize from Mb to bytes:
	ramsize <<= 20;

	mmu_init_bitmap();

	debug_print_string("\tSetting up virtual memory mapping... ");

	// Map the text section:
	mmu_map_interval(&text_start, &text_end, &text_start, MMU_MODE_CODE, MMU_PERM_RO_RO, NULL);
	// Map the data section:
	mmu_map_interval(&data_start, &data_page_end, &data_start, MMU_MODE_DATA, MMU_PERM_RW_NONE, NULL);
	// Map the kernel stack:
	mmu_map_interval(&stack_bottom, &stack_top,
		(void *) UNSIGNED_DIFF(&kernel_stack_top, UNSIGNED_DIFF(&stack_top, &stack_bottom)),
		MMU_MODE_STACK, MMU_PERM_RW_NONE, NULL);

	// Map the debug port until it can be properly mapped by the device initialization
	// routines:
	mmu_map_interval((void *) 0x49020000, (void *) ((uint32_t) 0x49020000 + (uint32_t) 4096),
		(void *) 0xc9020000, MMU_MODE_DEVICE, MMU_PERM_RW_NONE, NULL);

	// Map additional memory that may have been used to create page tables:
	uint32_t end_of_mapping = (uint32_t) &data_page_end;
	while((uint32_t) kernel_end > end_of_mapping)
	{
		uint32_t end_interval = (uint32_t) end_of_mapping + 4096;

		mmu_map_interval((void *) end_of_mapping, (void *) end_interval, (void *) end_of_mapping,
			MMU_MODE_DATA, MMU_PERM_RW_NONE, NULL);

		end_of_mapping = end_interval;
	}

	// Map in an extra page for the memory manager, so that there is at least
	// a minimum of memory available:
	mmu_map_interval((void *) end_of_mapping, (void *) end_of_mapping + 4096, (void *) end_of_mapping,
		MMU_MODE_DATA, MMU_PERM_RW_NONE, NULL);
	mmu_init();

	// Initialize the kernel memory manager
	dataspace_start = kernel_end;
	dataspace_end = (void *) end_of_mapping + 4096;

	// Finished initializing the kernel mapping:
	debug_print_string("ok");
	debug_print_newline();

	mmu_enabled = true;
}

// Allocates the specified amount of memory with the specified alignment.
void * mm_alloc(size_t size, int alignment)
{
	void * retval = NULL;

#ifdef DEBUG_MM
	debug_print_string("[mm_alloc] allocating ");
	debug_print_dec(size);
	debug_print_string(" bytes of memory with alignment ");
	debug_print_dec(alignment < 4 ? 4 : alignment);
	debug_print_newline();
#endif

	// Prevent alignment problems by making sure everything is aligned to 4 bytes:
	if(alignment < 4)
		alignment = 4;
	
	// Round size up to a multiple of 4, also to prevent alignment problems:
	size = (size + 3) & mask_left(4);

	// Before the MMU is enabled, we simply give away the space following the end of
	// the kernel data, as this memory will never be freed:
	if(!mmu_enabled)
	{
		if(((uint32_t) kernel_end & ~mask_left(alignment)) != 0)
			retval = (void *) (UNSIGNED_ADD(kernel_end, alignment - 1) & mask_left(alignment));
		else
			retval = (void *) kernel_end;
		kernel_end = retval + size;
	} else { // After the MMU is enabled, more advanced memory management is used.

		// Create the first memory block if neccessary:
		if(first_block == NULL)
		{
			if(UNSIGNED_DIFF(dataspace_end, dataspace_start) <= sizeof(mm_blk_info_t))
			{
				void * prev_dataspace = dataspace_end;
				mm_inc_dataspace();
				if(dataspace_end == prev_dataspace)
				{
					debug_print_string("[mm_alloc] out of memory!");
					debug_print_newline();
					return NULL;
				}
			}

			first_block = dataspace_start;
			first_block->prev_block = NULL;
			first_block->next_block = NULL;
			first_block->block_size = UNSIGNED_DIFF(dataspace_end, dataspace_start)
				- sizeof(mm_blk_info_t);
			first_block->used = false;
		}

		// Search through all blocks until a suitable one is found:
		mm_blk_info_t * block = first_block;
		while(block != NULL)
		{
			if(!block->used && block->block_size >= size)
			{
				// Start of returnable memory:
				void * memstart = (void *) UNSIGNED_ADD(block, sizeof(mm_blk_info_t));
				// Calculate the offset required for correct alignment:
				int offset = UNSIGNED_DIFF(
					((uint32_t) memstart + (alignment - 1)) & mask_left(alignment),
					memstart
				);

				if(offset == 0)
				{
					if(block->block_size > size)
						mm_split_block(block, size);
					block->used = true;
					retval = memstart;
				} else {
					// If possible, split the block and return memory that
					// is correctly aligned.
					if(offset > sizeof(mm_blk_info_t)
						&& block->block_size - offset > size)
					{
						mm_blk_info_t * temp = mm_split_block(block,
							offset - sizeof(mm_blk_info_t));
						temp->used = true;
						retval = (void *) UNSIGNED_ADD(temp, sizeof(mm_blk_info_t));

						if(temp->block_size > size)
							mm_split_block(temp, size);
					}
				}
			}

			if(retval != NULL)
				break;

			if(block->next_block == NULL)
			{
				mm_inc_dataspace();

				if(!block->used)
					block->block_size += 4096;
				else {
					mm_blk_info_t * new_block = (void *) UNSIGNED_DIFF(dataspace_end, 4096);

					block->next_block = new_block;
					new_block->prev_block = block;
					new_block->next_block = NULL;

					new_block->used = false;
					new_block->block_size = 4096 - sizeof(mm_blk_info_t);

					block = new_block;
				}
			} else
				block = block->next_block;
		}
	}

#ifdef DEBUG_MM
	debug_print_string("[mm_alloc] memory allocated @ ");
	debug_print_hex((uint32_t) retval);
	debug_print_string(" with size ");
	debug_print_dec(size);
	debug_print_newline();
#endif
	return retval;
}

// Frees a previously allocated block of memory:
void mm_free(void * memory)
{
	mm_blk_info_t * block = (mm_blk_info_t *) UNSIGNED_DIFF(memory, sizeof(mm_blk_info_t));

	block->used = false;
	if(block->next_block != NULL && !block->next_block->used)
		block = mm_merge_blocks(block, block->next_block);
	if(block->prev_block != NULL && !block->prev_block->used)
		mm_merge_blocks(block, block->prev_block);
}

// Merges two memory blocks:
// |---A---||---B---|  ===> |------A------|
mm_blk_info_t * mm_merge_blocks(mm_blk_info_t * a, mm_blk_info_t * b)
{
#ifdef DEBUG_MM
	debug_print_string("[mm_merge_blocks] merging blocks of size ");
	debug_print_dec(a->block_size);
	debug_print_string(" and ");
	debug_print_dec(a->block_size);
	debug_print_newline();
#endif

	a->block_size += b->block_size + sizeof(mm_blk_info_t);
	a->next_block = b->next_block;
	if(b->next_block != NULL)
		b->next_block->prev_block = a;
	
	return a;
}

// Splits a memory block at the specified offset (starting at the end of the
// block info structure); the new block info structure is created at the offset:
// |---A---I------| ===> |---A---||---B---|
mm_blk_info_t * mm_split_block(mm_blk_info_t * block, uint32_t offset)
{
#ifdef DEBUG_MM
	debug_print_string("[mm_split_block] splitting block @ ");
	debug_print_dec(offset);
	debug_print_newline();
#endif
	// Check if it is possible to split the block, or return NULL:
	if(block->block_size - offset <= sizeof(mm_blk_info_t))
		return NULL;

	mm_blk_info_t * new_block = (void *) block + sizeof(mm_blk_info_t) + offset;
//	new_block->used = block->used;
	new_block->used = false;

	new_block->block_size = block->block_size - offset - sizeof(mm_blk_info_t);
	block->block_size = offset;

	if(block->next_block != NULL)
		block->next_block->prev_block = new_block;
	new_block->next_block = block->next_block;
	new_block->prev_block = block;
	block->next_block = new_block;

	return new_block;
}

// Create a new memory block in the middle of another block, starting and ending in
// the specified positions:
// |---A---F---S------| ===> |---A---||F---S||-B-|
mm_blk_info_t * mm_cut_block(mm_blk_info_t * block, uint32_t first_index, uint32_t second_index)
{
}

// Increases the kernel dataspace by 1 page:
void mm_inc_dataspace()
{
	void * new_page = mmu_get_free_page();

	if(new_page == NULL)
		return;

	// If not, map the new page into kernel memory:
	mmu_map_interval(new_page, new_page + 4096, dataspace_end,
		MMU_MODE_DATA, MMU_PERM_RW_NONE, NULL);

	dataspace_end += (unsigned) 4096;
}

#ifdef DEBUG_MM
// Prints a list of blocks in memory:
void mm_print_block_list()
{
	mm_blk_info_t * block = first_block;

	while(block != NULL)
	{
		debug_print_string("Block @ ");
		debug_print_hex((void *) block);
		debug_print_char(':');
		debug_print_newline();

		debug_print_string("\tSize: ");
		debug_print_dec(block->block_size);
		debug_print_newline();

		debug_print_string("\tStatus: ");
		if(block->used)
			debug_print_string("used");
		else
			debug_print_string("free");
		debug_print_newline();

		block = block->next_block;
	}
}

#endif

