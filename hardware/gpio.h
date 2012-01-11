// SkordalOS: GPIO Bitfield Details
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_GPIO_H
#define HARDWARE_GPIO_H

// Number of GPIO modules:
#define GPIO_NUM_MODULES	6

// GPIO Module Base Addresses:
#define GPIO0_BASE	0x48310000
#define GPIO1_BASE	0x49050000
#define GPIO2_BASE	0x49052000
#define GPIO3_BASE	0x49054000
#define GPIO4_BASE	0x49056000
#define GPIO5_BASE	0x49058000

// GPIO Address Space Size:
#define GPIO_SPACE_SIZE	4096

// Register offsets:
#define GPIO_REVISION		0x00
#define GPIO_SYSCONFIG		0x10
#define GPIO_SYSSTATUS		0x14
#define GPIO_OE			0x34
#define GPIO_DATAIN		0x38
#define GPIO_DATAOUT		0x3c
#define GPIO_CLEARDATAOUT	0x90
#define GPIO_SETDATAOUT		0x94

// Idle mode bits:
#define GPIO_SYSCONFIG_IDLEMODE_FORCE	(0x0 << 3)
#define GPIO_SYSCONFIG_IDLEMODE_NONE	(0x1 << 3)
#define GPIO_SYSCONFIG_IDLEMODE_SMART	(0x2 << 3)

#endif

