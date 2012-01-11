// SkordalOS Debug Functions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef DEBUG_H
#define DEBUG_H

#include "types.h"

#include "hardware/macros.h"
#include "hardware/uart.h"

extern bool mmu_enabled;

// Prints a string to the debug console:
void debug_print_string(const char * string);
// Prints a newline to the debug console:
void debug_print_newline();

// Prints a 32-bit hexadecimal number to the debug console:
void debug_print_hex(uint32_t number);

// Prints a 32-bit number as a decimal number to the debug console:
void debug_print_dec(uint32_t number);

// Prints a 32-bit bitfield:
void debug_print_bitfield(uint32_t number);

// Prints a single character to the debug console:
void debug_print_char(char character);

#endif

