// SkordalOS I2C Register Definitions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_I2C_H
#define HARDWARE_I2C_H

// Base addresses for the various I2C modules:
#define I2C0_BASE	0x48070000
#define I2C1_BASE	0x48072000
#define I2C2_BASE	0x48060000

// Easy access to the base addresses:
#define I2C_BASE(n)	\
	n == 0 ? I2C0_BASE : \
	n == 1 ? I2C1_BASE : \
	n == 2 ? I2C2_BASE : \
	NULL

// Register offsets:
#define I2C_REV		0x00
#define I2C_IE		0x04
#define I2C_STAT	0x08
#define I2C_CNT		0x18
#define I2C_DATA	0x1c
#define I2C_CON		0x24
#define I2C_SA		0x2c
#define I2C_PSC		0x30
#define I2C_SPLL	0x34
#define I2C_SPLH	0x38

// I2C_IE bitfield names:
#define I2C_XDR_IE	(1 << 14)
#define I2C_RDR_IE	(1 << 13)
#define I2C_ROVR_IE	(1 << 11)
#define I2C_XUDF_IE	(1 << 10)
#define I2C_AAS_IE	(1 <<  9)
#define I2C_BF_IE	(1 <<  8)
#define I2C_AERR_IE	(1 <<  7)
#define I2C_STC_IE	(1 <<  6)
#define I2C_GC_IE	(1 <<  5)
#define I2C_XRDY_IE	(1 <<  4)
#define I2C_RRDY_IE	(1 <<  3)
#define I2C_ARDY_IE	(1 <<  2)
#define I2C_NACK_IE	(1 <<  1)
#define I2C_AL_IE	(1 <<  0)

// I2C_STAT bitfield names:
#define I2C_XDF		(1 << 14)
#define I2C_EDE		(1 << 13)
#define I2C_BB		(1 << 12)
#define I2C_ROVR	(1 << 11)
#define I2C_XUDF	(1 << 10)
#define I2C_AAS		(1 <<  9)
#define I2C_BF		(1 <<  8)
#define I2C_AERR	(1 <<  7)
#define I2C_STC		(1 <<  6)
#define I2C_GC		(1 <<  5)
#define I2C_XRDY	(1 <<  4)
#define I2C_RRDY	(1 <<  3)
#define I2C_ARDY	(1 <<  2)
#define I2C_NACK	(1 <<  1)
#define I2C_AL		(1 <<  0)

// I2C_CON bitfield names:
#define I2C_EN		(1 << 15)
#define I2C_MST		(1 << 10)
#define I2C_TRX		(1 <<  9)
#define I2C_STP		(1 <<  1)
#define I2C_STT		(1 <<  0)

#endif

