// SkordalOS: SDRC Register Definitions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_SDRC_H
#define HARDWARE_SDRC_H

// SDRC module base address:
#define SDRC_BASE	0x6d000000

// SDRC register names and offsets:
#define SDRC_REVISION	0x00
#define SDRC_MCFG_CS0	0x80
#define SDRC_MCFG_CS1	0xb0

// SDRC macros:
#define SDRC_EXTRACT_RAMSIZE(mcfg)	((mcfg >> 8) & 0x3ff)

#endif

