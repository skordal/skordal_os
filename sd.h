// SkordalOS SD card driver
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef SD_H
#define SD_H

#include "types.h"

#include "hardware/macros.h"
#include "hardware/mmchs.h"

#include "debug.h"
#include "gpio.h"
#include "mmu.h"

// Initializes the SD card module. On the BeagleBoard, only the first MMC
// interface is used for anything, so only the first MMC interface is used
// here:
void sd_init();

#endif

