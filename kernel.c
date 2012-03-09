// SkordalOS Kernel
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "kernel.h"

// Seconds of uptime counter:
static uint64_t uptime_counter = 0;

// Initializes the kernel, devices and related structures:
void kernel_init()
{
	// Start power management:
	pm_init();

	// Set up IRQ handling:
	irq_init();

	// Initialize the TPS65950 power chip:
	tps65950_init();

	// Initialize the GPIO driver:
	gpio_init();

	// Set up the uptime timer:
	timer_reset(1, TIMER_MODE_AUTORELOAD, 1 * TIMER_SECOND, kernel_update_uptime);
	timer_start(1);

	// Initialize the SD card interface:
	sd_init();

	// We are now completely initialized:
	debug_print_string("Kernel started successfully.");
	debug_print_newline();
}

// Kernel main loop:
void __attribute((noreturn)) kernel_main()
{
	while(1) asm volatile("wfi\n\t");
}

// Updates the uptime counter:
void kernel_update_uptime()
{
	++uptime_counter;

	// Make one of the GPIOs into an uptime clock:
	gpio_toggle(GPIO_USER_LED0);
}

