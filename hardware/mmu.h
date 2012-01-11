// SkordalOS: MMU Definitions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_MMU_H
#define HARDWARE_MMU_H

// First level descriptor table entry types:
#define MMU_L1_TYPE_FAULT		0b00
#define MMU_L1_TYPE_PAGE_TABLE		0b01
#define MMU_L1_TYPE_SECTION		0b10
#define MMU_L1_TYPE_SUPERSECTION	0b10|(1 << 18)

// The bitmask used for extracting the address from a page table entry:
#define MMU_L1_PAGE_TABLE_ADDRESS_MASK	0xfffffc00

// Second level descriptor table entry types:
#define MMU_L2_TYPE_FAULT	0b00
#define MMU_L2_TYPE_SMALL_PAGE	0b10
#define MMU_L2_TYPE_LARGE_PAGE	0b01

// Second level descriptor table entry fields:
#define MMU_L2_SP_XN	(1 <<  0)
#define MMU_L2_SP_B	(1 <<  2)
#define MMU_L2_SP_C	(1 <<  3)
#define MMU_L2_SP_AP0	(1 <<  4)
#define MMU_L2_SP_AP1	(1 <<  5)
#define MMU_L2_SP_TEX0	(1 <<  6)
#define MMU_L2_SP_TEX1	(1 <<  7)
#define MMU_L2_SP_TEX2	(1 <<  8)
#define MMU_L2_SP_AP2	(1 <<  9)
#define MMU_L2_SP_S	(1 << 10)
#define MMU_L2_SP_nG	(1 << 11)

// The bitmask used for extracting the address from a small page entry:
#define MMU_L2_SMALL_PAGE_ADDRESS_MASK	0xfffff000

#endif

