// SkordalOS TPS65950 Driver
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef TPS65950_H
#define TPS65950_H

#include "i2c.h"

// Initializes the TPS65950:
void tps65950_init();

// Reads a TPS65950 register:
uint8_t tps65950_read_reg(uint8_t bank, uint8_t reg);

// Writes a TPS65950 register:
void tps65950_write_reg(uint8_t bank, uint8_t reg, uint8_t data);

#endif

