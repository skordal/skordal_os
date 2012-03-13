// SkordalOS Debug functions
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "debug.h"

// Prints a string to the debug console:
void debug_print_string(const char * restrict string)
{
	for(int i = 0; string[i] != 0; ++i)
		debug_print_char(string[i]);
}

// Prints a newline to the debug console:
void debug_print_newline()
{
	debug_print_char('\r');
	debug_print_char('\n');
}

// Prints a 32-bit hexadecimal number to the debug console:
void debug_print_hex(uint32_t number)
{
	// Volatile is neccessary so that the compiler does not destroy the
	// for loop when optimizing:
	static const char * volatile hex_digits = "0123456789abcdef";
	
	debug_print_char('0');
	debug_print_char('x');

	for(int i = 28; i >= 0; i -= 4)
		debug_print_char(hex_digits[number >> i & 0xf]);
}

// Prints a number as a decimal number to the debug console:
void debug_print_dec(uint32_t number)
{
	static char buffer[10] = "0000000000";
	bool inside_num = false;

	for(int i = 9; i >= 0; --i)
	{
		buffer[i] = (char) '0' + (number % 10);
		number /= 10;
	}

	for(int i = 0; i < 10; ++i)
	{
		if(!inside_num && buffer[i] == '0' && i != 9)
			continue;
		inside_num = true;
		debug_print_char(buffer[i]);
	}
}

// Prints a 32-bit bitfield:
void debug_print_bitfield(uint32_t bitfield)
{
	int separator_counter = 0;

	for(int i = 31; i >= 0; --i, ++separator_counter)
	{
		if(separator_counter == 8)
		{
			debug_print_char('|');
			separator_counter = 0;
		}

		if((bitfield >> i) & 1)
			debug_print_char('1');
		else
			debug_print_char('0');
	}
}

// Prints a single character to the debug console:
void debug_print_char(char character)
{
	// Make sure this function works both before and after
	// the MMU has been enabled:
	volatile uint32_t * uart_lsr_register = mmu_enabled ?
		HW_ADDR(REG_ADDR(UART2_BASE, UART_LSR_REG)) :
		REG_ADDR(UART2_BASE, UART_LSR_REG);
	volatile uint32_t * uart_thr_register = mmu_enabled ?
		HW_ADDR(REG_ADDR(UART2_BASE, UART_THR_REG)) :
		REG_ADDR(UART2_BASE, UART_THR_REG);

	while(!(*uart_lsr_register & UART_LSR_TX_FIFO_E));
	*((char *) uart_thr_register) = character;
}

