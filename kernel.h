// SkordalOS Kernel
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef KERNEL_H
#define KERNEL_H

#include "cpuid.h"
#include "debug.h"
#include "display.h"
#include "gpio.h"
#include "irq.h"
#include "pm.h"
#include "process.h"
#include "timer.h"
#include "tps65950.h"

// Initializes the kernel, which registers all devices and sets up neccessary
// structures and variables.
void kernel_init();

// This function provides the kernel main loop.
void __attribute((noreturn)) kernel_main();

// Callback function for the 1 second uptime timer:
void kernel_update_uptime();

#endif

