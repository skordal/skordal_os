// SkordalOS IRQ Handling Code
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "irq.h"

// IRQ handler array:
irq_handler_func irq_handler_array[NUM_IRQ_HANDLERS];

// Interrupt controller memory space:
volatile uint32_t * intc = HW_ADDR(INTC_BASE);

// Initializes the interrupt controller:
void irq_init()
{
	debug_print_string("Initializing interrupt controller:");
	debug_print_newline();

	mmu_map_interval((void *) INTC_BASE, (void *) (INTC_BASE + 4096),
		HW_ADDR(INTC_BASE), MMU_MODE_DEVICE, MMU_PERM_RW_NONE, NULL);

	uint32_t revision = intc[REG_32(INTC_REVISION)];
	debug_print_string("\tHardware revision: ");
	debug_print_dec(IP_REV_MAJOR(revision));
	debug_print_char('.');
	debug_print_dec(IP_REV_MINOR(revision));
	debug_print_newline();

	intc[REG_32(INTC_SYSCONFIG)] = INTC_AUTOIDLE;
	intc[REG_32(INTC_IDLE)] |= INTC_TURBO;
	intc[REG_32(INTC_PROTECTION)] = 1;
}

// Registers an IRQ interrupt handler:
void irq_register_handler(int irq, irq_handler_func handler)
{
	irq_handler_array[irq] = handler;
}

// Sets the specified IRQ to be handled as an FIQ:
void irq_set_as_fiq(int irq)
{
	intc[REG_32(INTC_ILR(irq))] |= 1;
}

// Enables the specified IRQ interrupt, with the specified priority (0x00 - 0x3f,
// 0x3f being the lowest priority, 0 being highest and default):
void irq_enable(int irq, int priority)
{
	// Which IRQ masking register to use:
	int reg = irq >> 5;
	int bit = irq & 0x1f;

#ifdef DEBUG_IRQ
	debug_print_string("[irq_enable] enabling IRQ ");
	debug_print_dec(irq);
	debug_print_string(" (");
	debug_print_dec(reg);
	debug_print_char(':');
	debug_print_dec(bit);
	debug_print_char(')');
	debug_print_newline();
#endif

	intc[REG_32(INTC_MIR_CLEAR(reg))] = 1 << bit;
	// TODO: Set the priority of the interrupt.
}

// Disables the specified IRQ interrupt:
void irq_disable(int irq)
{
	// Which IRQ masking register to use:
	int reg = (irq - 1) >> 5;
	int bit = (irq - 1) % 32;

#ifdef DEBUG_IRQ
	debug_print_string("[irq_disable] disabling IRQ ");
	debug_print_dec(irq);
	debug_print_newline();
#endif

	intc[REG_32(INTC_MIR_SET(reg))] = 1 << bit;
}

// Main IRQ handler function:
void irq_handler()
{
	int irq = intc[REG_32(INTC_SIR_IRQ)] & 0x7f;
	irq_handler_array[irq](irq);
	asm volatile("dsb\n\t");
	intc[REG_32(INTC_CONTROL)] = 1;
}

