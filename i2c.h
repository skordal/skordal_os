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

// Flags for the various functions below:
#define I2C_SEND_START	(1 << 0)
#define I2C_SEND_STOP	(1 << 1)

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

// Writes the specified data to the I2C bus:
void i2c_send(int module, uint8_t address, void * buffer, int flags);

// Reads the specified data over the I2C bus:
void i2c_read(int module, uint8_t address, void * buffer, int flags);

#endif

