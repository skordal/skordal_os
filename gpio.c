// SkordalOS GPIO Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "gpio.h"

// Gets the address of the module containing the specified GPIO pin:
inline volatile void * gpio_get_module_addr(int gpio);

// Initializes the GPIO interface:
void gpio_init()
{
	debug_print_string("Initializing GPIO interface:");
	debug_print_newline();
	debug_print_char('\t');

	// Map the GPIO modules:
	for(int i = 0; i < GPIO_NUM_MODULES; ++i)
	{
		volatile uint32_t * gpio_base;

		switch(i)
		{
			case 0:
				gpio_base = (void *) GPIO0_BASE;
				break;
			case 1:
				gpio_base = (void *) GPIO1_BASE;
				break;
			case 2:
				gpio_base = (void *) GPIO2_BASE;
				break;
			case 3:
				gpio_base = (void *) GPIO3_BASE;
				break;
			case 4:
				gpio_base = (void *) GPIO4_BASE;
				break;
			case 5:
				gpio_base = (void *) GPIO5_BASE;
				break;
		}

		// Map the module address space:
		mmu_map_interval(
			(void *) gpio_base,
			(void *) UNSIGNED_ADD(gpio_base, GPIO_SPACE_SIZE),
			HW_ADDR(gpio_base), MMU_MODE_DEVICE, MMU_PERM_RW_NONE, NULL);
		mmu_clear_tlb();

		gpio_base = HW_ADDR(gpio_base);

		debug_print_string("gpio");
		debug_print_dec(i);
		debug_print_char(' ');

		// Set module power management settings:
		gpio_base[REG_32(GPIO_SYSCONFIG)] |= GPIO_SYSCONFIG_IDLEMODE_SMART;
	}

	debug_print_newline();

	// Set the user LED GPIOs as outputs:
	gpio_set_mode(GPIO_USER_LED0, GPIO_MODE_OUTPUT);
	gpio_set_mode(GPIO_USER_LED1, GPIO_MODE_OUTPUT);

	// Set the user LEDs to off, initially:
	gpio_set_pin(GPIO_USER_LED0, false);
	gpio_set_pin(GPIO_USER_LED1, false);
}

// Sets the mode (input/output) for the specified GPIO pin:
void gpio_set_mode(int gpio, gpio_mode_t mode)
{
	volatile uint32_t * gpio_module = gpio_get_module_addr(gpio);
	int internal_gpio = gpio % 32;

#ifdef DEBUG_GPIO
	debug_print_string("[gpio_set_mode] setting GPIO ");
	debug_print_dec(gpio);
	if(GPIO_MODE_INPUT)
		debug_print_string(" to input");
	else
		debug_print_string(" to output");
	debug_print_newline();
#endif

	switch(mode)
	{
		case GPIO_MODE_INPUT:
			gpio_module[REG_32(GPIO_OE)] |= (1 << internal_gpio);
			break;
		case GPIO_MODE_OUTPUT:
			gpio_module[REG_32(GPIO_OE)] &= ~(1 << internal_gpio);
			break;
	}
}

// Turns a GPIO on or off:
void gpio_set_pin(int gpio, bool on)
{
	volatile uint32_t * gpio_module = gpio_get_module_addr(gpio);
	int internal_gpio = gpio % 32;

#ifdef DEBUG_GPIO
	debug_print_string("[gpio_set_pin] setting GPIO ");
	debug_print_dec(gpio);
	if(on)
		debug_print_string(" on");
	else
		debug_print_string(" off");
	debug_print_newline();
#endif

	if(on)
		gpio_module[REG_32(GPIO_SETDATAOUT)] = (1 << internal_gpio);
	else
		gpio_module[REG_32(GPIO_CLEARDATAOUT)] = (1 << internal_gpio);
}

// Toggles a GPIO pin:
void gpio_toggle(int gpio)
{
	volatile uint32_t * gpio_module = gpio_get_module_addr(gpio);
	int internal_gpio = gpio % 32;

	uint32_t current_state = gpio_module[REG_32(GPIO_DATAOUT)];

	if(current_state & (1 << internal_gpio))
		gpio_module[REG_32(GPIO_CLEARDATAOUT)] = (1 << internal_gpio);
	else
		gpio_module[REG_32(GPIO_SETDATAOUT)] = (1 << internal_gpio);
}

// Gets the address of the module with the specified GPIO pin:
inline volatile void * gpio_get_module_addr(int gpio)
{
	int module = gpio / 32;

	switch(module)
	{
		case 0:
			return (volatile void *) HW_ADDR(GPIO0_BASE);
		case 1:
			return (volatile void *) HW_ADDR(GPIO1_BASE);
		case 2:
			return (volatile void *) HW_ADDR(GPIO2_BASE);
		case 3:
			return (volatile void *) HW_ADDR(GPIO3_BASE);
		case 4:
			return (volatile void *) HW_ADDR(GPIO4_BASE);
		case 5:
			return (volatile void *) HW_ADDR(GPIO5_BASE);
		default:
			debug_print_string("[gpio_get_module_addr] GPIO ");
			debug_print_dec(gpio);
			debug_print_string(" does not exist.");
			debug_print_newline();
			return NULL;
	}
}

