// SkordalOS Timer Interface
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef CPUID_H
#define CPUID_H

#include "types.h"
#include "debug.h"

typedef struct {
	struct {
		uint8_t major, minor;
	} revision;
	// Flags in feature register 0:
	bool thumbee_support, jazelle_support, thumb_support, thumb2_support;
	// Flags (of interest) in feature register 1:
	bool timer, virt, sec;
} cpuid_t;

extern cpuid_t cpuid;

// Initializes the CPUID struct:
void cpuid_init();

#endif

