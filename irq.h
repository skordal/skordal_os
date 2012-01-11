// SkordalOS IRQ Handling Code
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef IRQ_HANDLER_H
#define IRQ_HANDLER_H

#include "types.h"

#include "debug.h"
#include "mmu.h"

#include "hardware/macros.h"
#include "hardware/intc.h"

// The total number of IRQs in the system
#define NUM_IRQ_HANDLERS	96

// IRQ handler function pointer type:
typedef void (* irq_handler_func)(int number);

// IRQ setup function, initializes the interrupt controller:
void irq_init();

// Registers an interrupt handler for the specified IRQ:
void irq_register_handler(int irq, irq_handler_func function);

// Sets the specified interrupt to FIQ mode:
void irq_set_as_fiq(int irq);

// Enables the specified IRQ interrupt, with the specified priority (0x00 - 0x3f,
// 0x3f being the lowest priority, 0 being highest and default):
void irq_enable(int irq, int priority);

// Disables an IRQ interrupt:
void irq_disable(int irq);

// The IRQ handler is called from the IRQ handler in interrupts.S.
// When this function is entered, the processor is in SVC mode.
void irq_handler();

#endif

