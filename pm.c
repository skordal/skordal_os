// SkordalOS Power Management
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "pm.h"

// Initializes the power management driver:
void pm_init()
{
	volatile uint32_t * cm_memspace = HW_ADDR(PM_CM_BASE);
	volatile uint32_t * pm_memspace = HW_ADDR(PM_PRM_BASE);

	debug_print_string("Initializing power management: ");
	debug_print_newline();

	// Map the clock management registers:
	mmu_map_interval((void *) PM_CM_BASE, (void *) UNSIGNED_ADD(PM_CM_BASE, 0x2000),
		HW_ADDR(PM_CM_BASE), MMU_MODE_DEVICE, MMU_PERM_RW_NONE, NULL);
	// Map the power management registers:
	mmu_map_interval((void *) PM_PRM_BASE, (void *) UNSIGNED_ADD(PM_PRM_BASE, 0x2000),
		HW_ADDR(PM_PRM_BASE), MMU_MODE_DEVICE, MMU_PERM_RW_NONE, NULL);
	mmu_clear_tlb();

	uint32_t prm_revision = pm_memspace[REG_32(PM_PRM_REVISION)];
	debug_print_string("\tPRM revision: ");
	debug_print_dec(IP_REV_MAJOR(prm_revision));
	debug_print_char('.');
	debug_print_dec(IP_REV_MINOR(prm_revision));
	debug_print_newline();
}

// Sets the voltage of the VPLL2 voltage regulator:
void pm_set_vpll2(vpll2_mode_t mode)
{
	tps65950_write_reg(TPS65950_VPLL2_DEDICATED, mode);

#ifdef DEBUG_PM
	debug_print_string("[pm_set_vpll2] VPLL2 voltage set to mode ");
	debug_print_dec(mode);
	debug_print_newline();
#endif
}

// Reboots the system by resetting the entire board:
void __attribute((noreturn)) pm_reboot()
{
	volatile uint32_t * memspace = HW_ADDR(PM_PRM_BASE);
	memspace[REG_32(PM_PRM_RSTCTRL)] = 1 << 2;
	while(1); // Prevent compiler warnings.
}

