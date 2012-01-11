// SkordalOS Timer Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "cpuid.h"

// CPUID structure:
cpuid_t cpuid;

// Initializes the CPUID stuct:
void cpuid_init()
{
	uint32_t temp;

	debug_print_string("Processor information:");
	debug_print_newline();

	// Read the silicon ID register:
	asm volatile(
		"mrc p15, 1, %[temp], c0, c0, 7\n\t"
		: [temp] "=r" (temp)
	);

	cpuid.revision.major = IP_REV_MAJOR(temp);
	cpuid.revision.minor = IP_REV_MINOR(temp);

	debug_print_string("\tHardware revision: ");
	debug_print_dec(cpuid.revision.major);
	debug_print_char('.');
	debug_print_dec(cpuid.revision.minor);
	debug_print_newline();

	// Read the Processor feature register 0:
	asm volatile(
		"mrc p15, 0, %[temp], c0, c1, 0\n\t"
		: [temp] "=r" (temp)
	);

	cpuid.thumbee_support = (temp >> 12) & 1;
	cpuid.jazelle_support = ((temp >> 8) & 3) > 0;
	cpuid.thumb_support = (temp >> 4) & 1;
	cpuid.thumb2_support = (temp >> 5) & 1;

	debug_print_string("\tInstruction set support: ");
	if(cpuid.thumb_support)
		debug_print_string("thumb ");
	if(cpuid.thumb2_support)
		debug_print_string("thumb2 ");
	if(cpuid.thumbee_support)
		debug_print_string("thumbEE ");
	if(cpuid.jazelle_support)
		debug_print_string("jazelle ");
	debug_print_newline();

	// Read the Processor feature register 1:
	asm volatile(
		"mrc p15, 0, %[temp], c0, c1, 1\n\t"
		: [temp] "=r" (temp)
	);

	cpuid.timer = (temp >> 16) & 1;
	cpuid.virt = (temp >> 12) & 1;
	cpuid.sec = (temp > 4) & 1;

	debug_print_string("\tOther extensions: ");
	if(cpuid.timer)
		debug_print_string("timer ");
	if(cpuid.virt)
		debug_print_string("virt ");
	if(cpuid.sec)
		debug_print_string("sec ");
	debug_print_newline();
}

