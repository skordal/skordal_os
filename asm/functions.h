// Various Assembler Functions for SkordalOS
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef ASM_FUNCTIONS_H
#define ASM_FUNCTIONS_H

#include "../types.h"

// Masks the bits to the left of and including the leftmost set bit in
// the argument:
uint32_t mask_left(uint32_t number);

// Zeroes memory:
void zero_mem(void * address, size_t length);
void zero_mem_4(void * address, size_t length);

#endif

