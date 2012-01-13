// SkordalOS IVA2.2 driver
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "iva2.h"

// Initializes the IVA2.2 module by setting up its MMU tables:
void iva2_init()
{
	volatile uint32_t * iva_mmu = (volatile uint32_t *) MMU_IVA2_BASE;

	debug_print_string("Initializing IVA2.2 module:");
	debug_print_newline();

	// Set up a mapping of the IVA MMU:
	mmu_map_interval((void *) iva_mmu, (void *) UNSIGNED_ADD(iva_mmu, 4096),
		HW_ADDR(iva_mmu), MMU_MODE_DEVICE, MMU_PERM_RW_NONE, NULL);
	iva_mmu = (volatile uint32_t *) HW_ADDR(iva_mmu);

	debug_print_string("\tMMU revision: ");
	uint32_t revision = iva_mmu[REG_32(MMU_REVISION)];
	debug_print_dec(IP_REV_MAJOR(revision));
	debug_print_char('.');
	debug_print_dec(IP_REV_MINOR(revision));
	debug_print_newline();

	debug_print_string("\tNo IVA2.2 OS written yet!");
	debug_print_newline();
}

