// SkordalOS: Timer Bitfield Details
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_TIMERS_H
#define HARDWARE_TIMERS_H

// Timer module addresses:
#define TIMER0_BASE	0x48318000
#define TIMER1_BASE	0x49032000
#define TIMER2_BASE	0x49034000
#define TIMER3_BASE	0x49036000
#define TIMER4_BASE	0x49038000
#define TIMER5_BASE	0x4903a000
#define TIMER6_BASE	0x4903c000
#define TIMER7_BASE	0x4903e000
#define TIMER8_BASE	0x49040000
#define TIMER9_BASE	0x48086000
#define TIMER10_BASE	0x48088000

// Number of timers.
#define NUM_TIMERS	11

// Register offsets:
#define TIMER_TIDR	0x00
#define TIMER_TIOCP_CFG	0x10
#define TIMER_TISTAT	0x14
#define TIMER_TISR	0x18
#define TIMER_TIER	0x1c
#define TIMER_TCLR	0x24
#define TIMER_TCRR	0x28
#define TIMER_TLDR	0x2c
#define TIMER_TTGR	0x30

// TIOCP_CFG bitfield names:
#define TIMER_AUTOIDLE	(1 << 0)
#define TIMER_SOFTRESET	(1 << 1)
#define TIMER_ENAWAKEUP	(1 << 2)
#define TIMER_EMUFREE	(1 << 5)

// TISTAT bitfield name:
#define TIMER_RESETDONE	(1 << 0)

// TIOCP_CFG idle modes:
#define TIMER_IDLE_MODE_SMART	(0x2 << 3)

// TCLR bitfield names:
#define TIMER_TRG_OV	(1 << 10)
#define TIMER_CE	(1 <<  6)
#define TIMER_PRE	(1 <<  5)
#define TIMER_AR	(1 <<  1)
#define TIMER_ST	(1 <<  0)

// TISR bitfield names:
#define TIMER_OVF_IT_FLAG	(1 << 1)

// TIER bitfield names:
#define TIMER_TCAR_IT_ENA	(1 << 2)
#define TIMER_OVF_IT_ENA	(1 << 1)
#define TIMER_MAT_IT_ENA	(1 << 0)

#endif

