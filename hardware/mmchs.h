// SkordalOS MMC/SD/SDIO Register Definitions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_MMCHS_H
#define HARDWARE_MMCHS_H

#define MMCHS0_BASE	0x4809c000
#define MMCHS1_BASE	0x480b4000
#define MMCHS2_BASE	0x480ad000

// Register offsets:
#define MMCHS_SYSCONFIG	0x010
#define MMCHS_SYSSTATUS	0x014
#define MMCHS_CON	0x02c
#define MMCHS_SYSCTL	0x12c
#define MMCHS_CAPA	0x140
#define MMCHS_HCTL	0x128

// Bitfield names for MMCHS_SYSCONFIG:
#define MMCHS_SOFTRESET	(1 << 1)
#define MMCHS_AUTOIDLE	(1 << 0)

// Bitfield names for MMCHS_SYSSTATYS:
#define MMCHS_RESETDONE	(1 << 0)

// Bitfield names for MMCHS_CON:
#define MMCHS_CTPL	(1 << 11)
#define MMCHS_INIT	(1 <<  1)
#define MMCHS_OD	(1 <<  0)

// Bitfield names for MMCHS_SYSCTL:
#define MMCHS_CEN	(1 << 2)
#define MMCHS_ICS	(1 << 1)
#define MMCHS_ICE	(1 << 0)

// Bitfield names for MMCHS_CAPA:
#define MMCHS_VS18	(1 << 26)
#define MMCHS_VS30	(1 << 25)
#define MMCHS_VS33	(1 << 24)

// Bitfield names for MMCHS_HCTL:
#define MMCHS_SDVS_1V8	(0x5 << 9)
#define MMCHS_SDVS_3V0	(0x6 << 9)
#define MMCHS_SDVS_3V3	(0x7 << 9)
#define MMCHS_SDBP	(1   << 8)
#define MMCHS_DTW_1B	(0x0 << 1)
#define MMCHS_DTW_4B	(0x1 << 1)

#endif

