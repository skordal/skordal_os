// SkordalOS: Various Processor Related Definitions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_PROCESSOR_H
#define HARDWARE_PROCESSOR_H

// Processor modes:
#define PROCESSOR_MODE_USER	0b10000
#define PROCESSOR_MODE_FIQ	0b10001
#define PROCESSOR_MODE_IRQ	0b10010
#define PROCESSOR_MODE_SVC	0b10011
#define PROCESSOR_MODE_MON	0b10110
#define PROCESSOR_MODE_ABT	0b10111
#define PROCESSOR_MODE_HYP	0b11010
#define PROCESSOR_MODE_UND	0b11011
#define PROCESSOR_MODE_SYS	0b11111

// CPACR bitfield definitions:
#define CPACR_ASEDIS		(1 << 31)
#define CPACR_D32DIS		(1 << 30)
#define CPACR_TRCDIS		(1 << 29)

#define CPACR_COPROC(n)		(n <<  1)

#define CPACR_NO_ACCESS		0b00
#define CPACR_PRIV_ACCESS	0b01
#define CPACR_FULL_ACCESS	0b11


#endif

