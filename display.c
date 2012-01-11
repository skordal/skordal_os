// SkordalOS Display Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "display.h"

// Initializes the display system:
void display_init()
{
	// Enable the TFP410 chip:
	gpio_set_mode(GPIO_DVI_PUP, GPIO_MODE_OUTPUT);
	gpio_set_pin(GPIO_DVI_PUP, true);
}

