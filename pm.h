// SkordalOS Power Management
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef PM_H
#define PM_H

#include "macros.h"
#include "types.h"

#include "debug.h"
#include "mmu.h"
#include "tps65950.h"

#include "hardware/macros.h"
#include "hardware/pm.h"

// Available modes for the VPLL2 voltage regulator:
typedef enum {
	VPLL2_0V7  = 0,
	VPLL2_1V0  = 1,
	VPLL2_1V2  = 2,
	VPLL2_1V3  = 3,
	VPLL2_1V5  = 4,
	VPLL2_1V8  = 5,
	VPLL2_1V85 = 6,
	VPLL2_2V5  = 7,
	VPLL2_2V6  = 8,
	VPLL2_2V8  = 9,
	VPLL2_2V85 = 10,
	VPLL2_3V0  = 11,
	VPLL2_3V15 = 12,
} vpll2_mode_t;

// Initializes the Power Management driver:
void pm_init();

// Sets the voltage of the VPLL2 LDO:
void pm_set_vpll2(vpll2_mode_t mode);

// Reboots the system by resetting the entire board:
void __attribute((noreturn)) pm_reboot();

#endif

