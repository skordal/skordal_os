// SkordalOS TPS65950 Register Definitions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_TPS65950_H
#define HARDWARE_TPS65950_H

// Register bank, offset:

// PM_MASTER registers:
#define TPS65950_VPLL2_DEDICATED	0x4b, 0x91

// RTC registers:
#define TPS65950_SECONDS_REG		0x4b, 0x1c
#define TPS65950_MINUTES_REG		0x4b, 0x1d
#define TPS65950_HOURS_REG		0x4b, 0x1e
#define TPS65950_DAYS_REG		0x4b, 0x1f
#define TPS65950_MONTHS_REG		0x4b, 0x20
#define TPS65950_YEARS_REG		0x4b, 0x21
#define TPS65950_WEEKS_REG		0x4b, 0x22
#define TPS65950_RTC_CTRL_REG		0x4b, 0x29
#define TPS65950_RTC_STATUS_REG		0x4b, 0x2a

#endif

