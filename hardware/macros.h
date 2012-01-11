// SkordalOS Hardware Convenience Macros
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_MACROS_H
#define HARDWARE_MACROS_H

#include "../macros.h"

// Gets the address of a register by adding the base address and the register
// offset addresses:
#define REG_ADDR(base, offset) (void *)((uint32_t) base + (uint32_t)  offset)

// Gets the index for use with a 16 bit array into a hardware module's address
// space:
#define REG_16(offset) (offset >> 1)

// Gets the index for use with a 32 bit array into a hardware module's address
// space:
#define REG_32(offset) (offset >> 2)

// Gets the virtual address of a device based on its physical base address:
#define HW_ADDR(base)	(void *) UNSIGNED_ADD(base, 0x80000000)

// Extracts the minor revision from an IP revision field:
#define IP_REV_MINOR(field)	(field & 0xf)
// Extracts the major revision from an IP revision field:
#define IP_REV_MAJOR(field)	((field & 0xf0) >> 4)

#endif

