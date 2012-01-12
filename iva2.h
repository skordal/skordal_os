// SkordalOS IVA2.2 driver
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef IVA2_H
#define IVA2_H

#include "hardware/macros.h"
#include "hardware/mmu.h"

#include "macros.h"
#include "types.h"

#include "debug.h"
#include "mmu.h"

// Initializes the IVA2.2 by setting up its MMU translation table:
void iva2_init();

#endif

