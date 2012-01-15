// SkordalOS SD card driver
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "sd.h"

// Initializes the SD card interface:
void sd_init()
{
	volatile uint32_t * memspace = HW_ADDR(MMCHS0_BASE);

	debug_print_string("Initializing SD card interface: ");
	debug_print_newline();

	// Map the first MMCHS controller:
	mmu_map_interval((void *) MMCHS0_BASE,
		(void *) UNSIGNED_ADD(MMCHS0_BASE, 4096),
		(void *) HW_ADDR(MMCHS0_BASE),
		MMU_MODE_DEVICE, MMU_PERM_RW_NONE, NULL);
	mmu_clear_tlb();

	// Reset the controller:
	memspace[REG_32(MMCHS_SYSCONFIG)] = MMCHS_SOFTRESET;
	// Wait for the reset to finish:
	while(!(memspace[REG_32(MMCHS_SYSSTATUS)] & MMCHS_RESETDONE));
	// Set the autoidle bit:
	memspace[REG_32(MMCHS_SYSCONFIG)] |= MMCHS_AUTOIDLE;

	// Set voltage capabilities that are not automatically initialized:
	memspace[REG_32(MMCHS_CAPA)] |= MMCHS_VS18|MMCHS_VS30;

	// Set default voltage:
	memspace[REG_32(MMCHS_HCTL)] = MMCHS_SDVS_1V8;

	// Enable the card clock:
	memspace[REG_32(MMCHS_SYSCTL)] |= MMCHS_ICE|MMCHS_CEN;

	// Enable the SD bus power:
	memspace[REG_32(MMCHS_HCTL)] |= MMCHS_SDBP;
}

