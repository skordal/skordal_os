// SkordalOS MPU Interrupt Controller (INTC) definitions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_INTC_H
#define HARDWARE_INTC_H

// Interrupt controller base address:
#define INTC_BASE	0x48200000

// Register offsets:
#define INTC_REVISION	0x00
#define INTC_SYSCONFIG	0x10
#define INTC_SIR_IRQ	0x40
#define INTC_SIR_FIQ	0x44
#define INTC_CONTROL	0x48
#define INTC_PROTECTION	0x4c
#define INTC_IDLE	0x50

#define INTC_MIR_CLEAR(n)	(0x88 + (0x20 * n))
#define INTC_MIR_SET(n)		(0x8c + (0x20 * n))
#define INTC_ILR(n)		(0x100 + (0x4 * n))

// Bitfield names:

// For INTC_SYSCONFIG:
#define INTC_AUTOIDLE	(1 << 0)

// For INTC_IDLE:
#define INTC_TURBO	(1 << 1)

#endif

