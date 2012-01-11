// SkordalOS TPS65950 Driver
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "tps65950.h"

// Initializes the TPS65950 power chip:
void tps65950_init()
{
	// Initialize the I2C interface:
	i2c_init(0, I2C_100KHZ);
}

