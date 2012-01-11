// SkordalOS Timer Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef TIMER_H
#define TIMER_H

#include "macros.h"
#include "types.h"

#include "debug.h"
#include "irq.h"
#include "mmu.h"

#include "hardware/macros.h"
#include "hardware/timers.h"

// This is the default frequency for the timers:
#define TIMER_FREQUENCY	12000000

// Specifies how many microseconds are in a second:
#define TIMER_SECOND	1000000

// Gets the IRQ number of the specified timer:
#define TIMER_IRQ(timer)	(timer + 37)

typedef enum {
	TIMER_MODE_NONE,
	TIMER_MODE_ONESHOT,
	TIMER_MODE_AUTORELOAD,
} timer_mode_t;

typedef void (* timer_callback_func)();

// Resets/initializes the specified timer. Timer 0 is
// treated specially, as it is used for task switching
// and therefore set up as an FIQ.
void timer_reset(int timer, timer_mode_t mode, uint32_t usecs, timer_callback_func callback);

// Starts the specified timer:
void timer_start(int timer);

// Stops the specified timer:
void timer_stop(int timer);

// Timer IRQ handler:
void timer_irq_handler(int irq);

#endif

