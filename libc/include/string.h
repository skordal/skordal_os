// SkordalOS C Library
// (c) Kristian K. Skordal 2011 - 2012

// This file contains the standard C string functions.

#ifndef __SOS_STRING_H__
#define __SOS_STRING_H__

#include <sys/types.h>

// String length:
size_t strlen(const char * string);

// String copy functions:
char * strcpy(char * dest, const char * source);
char * strncpy(char * dest, const char * source, size_t length);

// Fills the specified memory area with a constant:
void * memset(void * memory_area, int constant, size_t length);

// Copies memory from one location to another:
void * memcpy(void * destination, const void * source, size_t length);

// Copies memory from one location to another and returns a pointer to the next
// byte after the the last written byte.
void * mempcpy(void * destination, const void * source, size_t length);

#endif

