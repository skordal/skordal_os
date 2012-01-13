// SkordalOS TPS65950 Driver
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "tps65950.h"

// Initializes the TPS65950 power chip:
void tps65950_init()
{
	// Initialize the I2C interface:
	i2c_init(0, I2C_100KHZ);
	i2c_set_master(0);

	debug_print_string("Initializing the TPS65950 power management chip: ");
	// Nothing in particular is done here yet.
	debug_print_string("ok");
	debug_print_newline();
}

// Reads a register:
uint8_t tps65950_read_reg(uint8_t bank, uint8_t reg) 
{
	uint8_t retval = 0;
	i2c_write(0, bank, &reg, 1, I2C_NO_STOP);
	i2c_read(0, bank, &retval, 1, I2C_NO_WAIT_FREE);
	return retval;
}

// Writes a register:
void tps65950_write_reg(uint8_t bank, uint8_t reg, uint8_t data)
{
	uint8_t buffer[2] = {reg, data};
	i2c_write(0, bank, buffer, 2, 0);
}

