// SkordalOS Timer Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "timer.h"

// Specifies how many timer ticks are in a microsecond.
#define TIMER_USEC	12

// Used for determining the physical address of the timer modules:
#define TIMER_ADDR(hw_addr)	UNSIGNED_DIFF(hw_addr, 0x80000000)

// Information structure for the various timers:
static struct {
	volatile uint32_t * memspace;
	timer_mode_t mode;
	uint32_t usec;
	timer_callback_func callback;
} timers[] = {
	{ HW_ADDR(TIMER0_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER1_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER2_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER3_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER4_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER5_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER6_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER7_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER8_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER9_BASE), TIMER_MODE_NONE, 0, NULL },
	{ HW_ADDR(TIMER10_BASE), TIMER_MODE_NONE, 0, NULL },
};

// Initializes the specified timer:
void timer_reset(int timer, timer_mode_t mode, uint32_t usec, timer_callback_func callback)
{
	debug_print_string("Initializing timer");
	debug_print_dec(timer);
	debug_print_string(": ");
	debug_print_newline();

	mmu_map_interval(
		(void *) TIMER_ADDR(timers[timer].memspace),
		(void *) TIMER_ADDR(timers[timer].memspace) + 4096,
		(void *) timers[timer].memspace, MMU_MODE_DEVICE, MMU_PERM_RW_NONE,
		NULL);

	timers[timer].mode = mode;
	timers[timer].usec = usec;
	timers[timer].callback = callback;

	// Reset the timer:
	timers[timer].memspace[REG_32(TIMER_TIOCP_CFG)] |= TIMER_SOFTRESET;
	while(!(timers[timer].memspace[REG_32(TIMER_TISTAT)] & TIMER_RESETDONE));

	// Print hardware revision:
	debug_print_string("\tHardware revision: ");
	debug_print_dec(IP_REV_MAJOR(timers[timer].memspace[REG_32(TIMER_TIDR)]));
	debug_print_char('.');
	debug_print_dec(IP_REV_MINOR(timers[timer].memspace[REG_32(TIMER_TIDR)]));
	debug_print_newline();

	// Set idle-mode to smart mode:
	timers[timer].memspace[REG_32(TIMER_TIOCP_CFG)] |= TIMER_IDLE_MODE_SMART;

	// Calculate the value to store in the timer registers:
	uint32_t timer_value = UNSIGNED_DIFF(0xffffffff, usec * TIMER_USEC);

	// Set timer parameters:
	debug_print_string("\tMode: ");
	switch(mode)
	{
		case TIMER_MODE_NONE:
			debug_print_string("invalid! Timer disabled.");
			debug_print_newline();
			return;
		case TIMER_MODE_ONESHOT:
			timers[timer].memspace[REG_32(TIMER_TCLR)] |= TIMER_TRG_OV;
			debug_print_string("one-shot");
			break;
		case TIMER_MODE_AUTORELOAD:
			timers[timer].memspace[REG_32(TIMER_TCLR)] |= TIMER_TRG_OV|TIMER_AR;
			debug_print_string("autoreload");
			break;
	}
	debug_print_newline();

	debug_print_string("\tInterval: ");
	debug_print_dec(usec);
	debug_print_string(" microseconds");
	debug_print_newline();

	timers[timer].memspace[REG_32(TIMER_TLDR)] = timer_value;
	timers[timer].memspace[REG_32(TIMER_TTGR)] = 1;

	// Set up the IRQ interrupt handler:
	irq_register_handler(timer + 37, timer_irq_handler);

	// Enable the overflow interrupt:
	timers[timer].memspace[REG_32(TIMER_TIER)] = 2;
}

// Starts the specified timer:
void timer_start(int timer)
{
	// Enable the timer interrupt:
	irq_enable(TIMER_IRQ(timer), 0);
	// Start the timer:
	timers[timer].memspace[REG_32(TIMER_TCLR)] |= TIMER_ST;
}

// Stops the specified timer:
void timer_stop(int timer)
{
	// Disables the timer interrupt:
	irq_disable(TIMER_IRQ(timer));
	// Stops the timer:
	timers[timer].memspace[REG_32(TIMER_TCLR)] &= ~TIMER_ST;
}

// The timer IRQ handler:
void timer_irq_handler(int irq)
{
	int timer = irq - 37;

	// Call the callback function for a timer, if any:
	if(timers[timer].callback != NULL)
		timers[timer].callback();

	// Clear the interrupt flag by writing to the correct bit of the TISR register:
	timers[timer].memspace[REG_32(TIMER_TISR)] |= TIMER_OVF_IT_FLAG;
}

