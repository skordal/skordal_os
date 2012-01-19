// SkordalOS MMU Functions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef MMU_H
#define MMU_H

#include "types.h"
#include "macros.h"
#include "hardware/mmu.h"
#include "asm/functions.h"

// Define to enable MMU function debugging:
//#define DEBUG_MMU	1

#define MMU_GET_L1_INDEX(addr) (addr >> 20)
#define MMU_GET_L2_INDEX(addr) ((addr & 0x000fffff) >> 12)

typedef enum {
	MMU_MODE_DEVICE,
	MMU_MODE_DATA,
	MMU_MODE_STACK,
	MMU_MODE_CODE
} mmu_mode_t;

// Permission type for the MMU functions, the symbols specify the permissions in the
// following format:
// 	MMU_PERM_KERNEL_USER
typedef enum {
	MMU_PERM_RW_RW,
	MMU_PERM_RW_RO,
	MMU_PERM_RW_NONE,
	MMU_PERM_RO_RO,
	MMU_PERM_RO_NONE,
	MMU_PERM_NONE_NONE // This might be a little pointless...
} mmu_perm_t;

extern bool mmu_enabled;

// Initializes the MMU control registers. The only action needed after calling this
// function is to actually enable the MMU by writing to the SCTLR register.
void mmu_init();

// Sets the current TTBR0 register value:
void mmu_set_ttbr0(void * new_table, pid_t asid);

// Clears the TLB:
void mmu_clear_tlb();

// Maps the specified interval of physical memory to to the corresponding interval
// of virtual memory starting at the specified virtual address. The descriptor table
// is the descriptor table to create the mapping in, if NULL the kernel table is used.
void mmu_map_interval(void * start_address, void * end_address, void * virtual_address,
	mmu_mode_t mode, mmu_perm_t permissions, uint32_t * descriptor_table);

// Unmaps the specified interval of virtual memory:
void mmu_unmap_interval(void * start_address, void * end_address, uint32_t * descriptor_table);

// Initializes the page bitmap:
void mmu_init_bitmap();

// Gets the address of a free page in RAM and marks it as used in the page bitmap:
void * mmu_get_free_page();
// Marks a page as used in the page bitmap:
void mmu_mark_as_used(void * page_address);
// Marks a page as unused in the page bitmap:
void mmu_mark_as_free(void * page_address);

// Finds the index of the first free page in the page table, for quicker returning
// the next free page when requested:
void mmu_find_next_index();

#endif

