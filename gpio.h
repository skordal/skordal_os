// SkordalOS GPIO Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef GPIO_H
#define GPIO_H

#include "debug.h"
#include "macros.h"
#include "mmu.h"
#include "types.h"

#include "hardware/macros.h"
#include "hardware/gpio.h"

// The following GPIOs are used for something on the BeagleBoard:
#define GPIO_USER_LED0	149
#define GPIO_USER_LED1	150
#define GPIO_MMC1_WP	 23
#define GPIO_DVI_PUP	170
#define GPIO_USER_BTN	  7

typedef enum {
	GPIO_MODE_INPUT,
	GPIO_MODE_OUTPUT
} gpio_mode_t;

// Initializes the GPIO interface:
void gpio_init();

// Sets the mode of the specified GPIO pin:
void gpio_set_mode(int gpio, gpio_mode_t mode);

// Turns a pin on or off:
void gpio_set_pin(int gpio, bool on);

// Toggles a GPIO pin:
void gpio_toggle(int gpio);

// Gets the address of the module containing the specified GPIO pin:
volatile void * gpio_get_module_addr(int gpio);

#endif

