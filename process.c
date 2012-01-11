// SkordalOS Process Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "process.h"

static pid_t next_pid = 1;
static process_t * first_process;
static process_t * active_process;

// Initializes the process manager:
void process_init_mgr()
{
	timer_reset(0, TIMER_MODE_AUTORELOAD, 500, NULL);
	timer_start(0);
}

// Creates a process:
process_t * process_create(void * buffer)
{
	return NULL;
}

// Process switch handler:
void process_switch_handler()
{
	// Pointer to the user registers from the IRQ handler:
	extern uint32_t * user_registers;

	// Check for the currently active process or process to switch to:
	if(active_process == NULL)
		return;
	
	// TODO: Write the rest. Remember to store NEON registers.
}

