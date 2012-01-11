// SkordalOS Power Management Register Definitions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_PM_H
#define HARDWARE_PM_H

// Clock management register base:
#define PM_CM_BASE	0x48004000
// Power and reset management register base:
#define PM_PRM_BASE	0x48306000

// CM registers:

// PRM register offsets:
#define PM_PRM_REVISION	0x0804
#define PM_PRM_RSTCTRL	0x1250

#endif

