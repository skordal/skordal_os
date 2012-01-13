// SkordalOS I2C Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "i2c.h"

struct {
	volatile uint16_t * memspace;
	bool master;
} i2c_controllers[] = {
	{ HW_ADDR(I2C_BASE(0)), false },
	{ HW_ADDR(I2C_BASE(1)), false },
	{ HW_ADDR(I2C_BASE(2)), false }
};

// Programmes the I2C registers for a transfer:
inline void i2c_program(int module, uint8_t address, uint16_t configuration, size_t length);
// Sends or receives I2C data via polling:
inline void i2c_loop(int module, uint8_t address, uint16_t configuration, uint8_t*  buffer, size_t length);

// Initializes the specified I2C module:
void i2c_init(int module, i2c_speed_mode_t speed)
{
	if(module > 2)
		return;

	debug_print_string("Initializing i2c");
	debug_print_dec(module);
	debug_print_char(':');
	debug_print_newline();

	// Map the module address space:
	if(module == 0 || module == 1)
		mmu_map_interval((void *) I2C0_BASE, (void *) UNSIGNED_ADD(I2C0_BASE, 4096),
			HW_ADDR(I2C0_BASE), MMU_PERM_RW_NONE, MMU_MODE_DEVICE, NULL);
	else
		mmu_map_interval((void *) I2C2_BASE, (void *) UNSIGNED_ADD(I2C2_BASE, 4096),
			HW_ADDR(I2C2_BASE), MMU_PERM_RW_NONE, MMU_MODE_DEVICE, NULL);
	mmu_clear_tlb();
	
	volatile uint16_t * memspace = HW_ADDR(I2C_BASE(module));

	// Ensure the module is deactivated while initializing:
	memspace[REG_16(I2C_CON)] &= ~I2C_EN;

	uint16_t revision = memspace[REG_16(I2C_REV)];
	debug_print_string("\tHardware revision: ");
	debug_print_dec(IP_REV_MAJOR(revision));
	debug_print_char('.');
	debug_print_dec(IP_REV_MINOR(revision));
	debug_print_newline();

	// Set the prescaler value to obtain a clock of 12 MHz:
	memspace[REG_16(I2C_PSC)] = 0x7;

	// Set the speed registers:
	debug_print_string("\tSpeed: ");
	if(speed == I2C_100KHZ)
	{
		debug_print_string("100 KHz");
		memspace[REG_16(I2C_SPLL)] = 0x35;
		memspace[REG_16(I2C_SPLH)] = 0x37;
	} else {
		// TODO: Test that this works.
		debug_print_string("400 KHz");
		memspace[REG_16(I2C_SPLL)] = 0x08;
		memspace[REG_16(I2C_SPLH)] = 0x0a;
	}
	debug_print_newline();

	// Enable the controller:
	memspace[REG_16(I2C_CON)] |= I2C_EN;
}

// Sets the specified I2C module to master mode:
void i2c_set_master(int module)
{
	i2c_controllers[module].master = true;
	// Set the master bit:
	i2c_controllers[module].memspace[REG_16(I2C_CON)] |= I2C_MST;
}

// Sets the specified I2C module to slave mode:
void i2c_set_slave(int module)
{
	i2c_controllers[module].master = false;
	// Unset the master bit in the control register if set:
	i2c_controllers[module].memspace[REG_16(I2C_CON)] &= ~I2C_MST;
}

// Writes the specified data to the I2C bus:
int i2c_write(int module, uint8_t address, uint8_t * buffer, size_t length, int flags)
{
	uint16_t conf = I2C_EN
		| (i2c_controllers[module].master ? I2C_MST : 0)	// Set MST bit.
		| (flags & I2C_NO_STOP ? 0 : I2C_STP)			// Set STP bit.
		| (flags & I2C_NO_START ? 0 : I2C_STT)			// Set STT bit.
		| I2C_TRX;						// Set TRX bit.

	// Wait for the bus to be free:
	if(!(flags & I2C_NO_WAIT_FREE))
		while(i2c_controllers[module].memspace[REG_16(I2C_STAT)] & I2C_BB);
	
	// Program the registers:
	i2c_program(module, address, conf, length);

	// Do the transfer:
	i2c_loop(module, address, conf, buffer, length);

	return 1;
}

// Reads the specified data from the I2C bus:
int i2c_read(int module, uint8_t address, uint8_t * buffer, size_t length, int flags)
{
	uint16_t conf =	I2C_EN
		| (i2c_controllers[module].master ? I2C_MST : 0)	// Set MST bit.
		| (flags & I2C_NO_STOP ? 0 : I2C_STP)			// Set STP bit.
		| (flags & I2C_NO_START ? 0 : I2C_STT);			// Set STT bit.

	// Wait for the bus to be free:
	if(!(flags & I2C_NO_WAIT_FREE))
		while(i2c_controllers[module].memspace[REG_16(I2C_STAT)] & I2C_BB);

	// Program the registers:
	i2c_program(module, address, conf, length);

	// Do the transfer:
	i2c_loop(module, address, conf, buffer, length);

	return 1;
}

// Sets up the I2C registers for transfer:
inline void i2c_program(int module, uint8_t address, uint16_t configuration, size_t length)
{
	while(!(i2c_controllers[module].memspace[REG_16(I2C_STAT)] & I2C_ARDY));
	i2c_controllers[module].memspace[REG_16(I2C_STAT)] |= I2C_ARDY;

	i2c_controllers[module].memspace[REG_16(I2C_CON)] = configuration;
	i2c_controllers[module].memspace[REG_16(I2C_SA)] = address;
	i2c_controllers[module].memspace[REG_16(I2C_CNT)] = length;
}

// Sends or receives data over the I2C bus using the polling method:
inline void i2c_loop(int module, uint8_t address, uint16_t conf, uint8_t * data, size_t length)
{
	int data_index = 0;

	do {
		uint16_t status = i2c_controllers[module].memspace[REG_16(I2C_STAT)];

		if(status & I2C_NACK)
		{
			i2c_controllers[module].memspace[REG_16(I2C_STAT)] |= I2C_NACK;
			i2c_program(module, address, conf, length);
		} else if(status & I2C_AL)
		{
			i2c_controllers[module].memspace[REG_16(I2C_STAT)] |= I2C_AL;
			i2c_program(module, address, conf, length);
		} else if(status & I2C_ARDY)
		{
			i2c_controllers[module].memspace[REG_16(I2C_STAT)] |= I2C_ARDY;
		} else if(status & I2C_XRDY)
		{
			i2c_controllers[module].memspace[REG_16(I2C_DATA)] = data[data_index++];
			i2c_controllers[module].memspace[REG_16(I2C_STAT)] |= I2C_XRDY;
		} else if(status & I2C_RRDY)
		{
			data[data_index++] = i2c_controllers[module].memspace[REG_16(I2C_DATA)];
			i2c_controllers[module].memspace[REG_16(I2C_STAT)] |= I2C_RRDY;
		}
	} while(data_index < length);
}

