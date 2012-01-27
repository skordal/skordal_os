// SkordalOS Test Support Macros
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef TEST_SUPPORT_H
#define TEST_SUPPORT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>

// Macros translating SkordalOS memory management functions to C memory
// management functions:
#define mm_alloc(x, y)	malloc(x)
#define mm_free(x)	free(x)

// Zeroes the specified memory:
#define zero_mem_4(x, y)	memset(x, 0, y)

#endif

