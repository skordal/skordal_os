// SkordalOS I2C Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef I2C_H
#define I2C_H

#include "types.h"

#include "hardware/macros.h"
#include "hardware/i2c.h"

#include "debug.h"
#include "irq.h"
#include "mmu.h"

// Possible flags for the various functions below:
#define I2C_NO_START		(1 << 0) // Don't send start byte
#define I2C_NO_STOP		(1 << 1) // Don't send stop byte
#define I2C_NO_WAIT_FREE	(1 << 2) // Don't wait for a free bus.

// I2C speeds:
typedef enum {
	I2C_100KHZ,
	I2C_400KHZ
} i2c_speed_mode_t;

// Initializes the specified I2C module:
void i2c_init(int module, i2c_speed_mode_t speed);

// Sets the specified module to master mode:
void i2c_set_master(int module);

// Sets the specified module to slave mode:
void i2c_set_slave(int module);

// Writes the specified data to the I2C bus, and returns 1 if the transfer
// was successful.
int i2c_write(int module, uint8_t address, uint8_t * buffer, size_t length, int flags);

// Reads the specified data from the I2C bus and returns 1 if the transfer
// was successful.
int i2c_read(int module, uint8_t address, uint8_t * buffer, size_t length, int flags);

#endif

