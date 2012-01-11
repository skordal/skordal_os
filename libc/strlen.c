// SkordalOS C Library
// (c) Kristian K. Skordal 2011 - 2012

#include "string.h"

size_t strlen(const char * string)
{
	int retval = 0;
	while(*++string != 0) ++retval;
	return retval;
}

