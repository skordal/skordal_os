// SkordalOS Preprocessor Macros
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef MACROS_H
#define MACROS_H

// Guarantees an unsigned subtraction of the values (which must be 32 bit at the moment):
#define UNSIGNED_DIFF(x, y) (((uint32_t) x) - ((uint32_t) y))
// Guarantees an unsigned add operation:
#define UNSIGNED_ADD(x, y) (((uint32_t) x) + ((uint32_t) y))

#endif

