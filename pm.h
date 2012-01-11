// SkordalOS Power Management
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef PM_H
#define PM_H

#include "macros.h"
#include "types.h"

#include "debug.h"
#include "mmu.h"

#include "hardware/macros.h"
#include "hardware/pm.h"

// Initializes the Power Management driver:
void pm_init();

// Resets the board, as in "reboot":
void __attribute((noreturn)) pm_reset();

#endif

