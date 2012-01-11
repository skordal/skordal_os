// SkordalOS Memory Manager Functions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef MM_H
#define MM_H

#include "types.h"

#include "debug.h"
#include "macros.h"
#include "mmu.h"

#include "asm/functions.h"

#include "hardware/macros.h"
#include "hardware/mmu.h"
#include "hardware/sdrc.h"

// Define to enable memory management debugging:
//#define DEBUG_MM 1

// The size of RAM in bytes:
extern uint32_t ramsize;

// Memory block info structure:
typedef struct __mm_blk_info_t {
	struct __mm_blk_info_t * next_block;
	struct __mm_blk_info_t * prev_block;
	size_t block_size;
	bool used;
} mm_blk_info_t;

// Initializes the kernel memory manager and sets up the initial MMU mapping:
void mm_init();

// Allocates the specified amount of memory with the given alignment (0 gives 4, the default).
// Returns NULL if not enough memory was available, otherwise returns a pointer to the
// allocated chunk of memory:
void * mm_alloc(size_t size, int alignment) __attribute((warn_unused_result));
// Frees a previously allocated chunk of memory:
void mm_free(void * memory);

// Merges the two block information headers specified:
mm_blk_info_t * mm_merge_blocks(mm_blk_info_t * a, mm_blk_info_t * b);
// Splits the a block in two at the specified position:
mm_blk_info_t * mm_split_block(mm_blk_info_t * block, uint32_t offset);
// Creates a block in the middle of another block, at the two specified cut indexes:
mm_blk_info_t * mm_cut_block(mm_blk_info_t * block, uint32_t first_split, uint32_t second_split);

// Increases the kernel dataspace by 1 page:
void mm_inc_dataspace();

#ifdef DEBUG_MM
// Prints a list of the currently allocated (both used and free) blocks in memory:
void mm_print_block_list();
#endif

#endif

