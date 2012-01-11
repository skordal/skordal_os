// SkordalOS Preprocessor Macros for Inline Assembler Use
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef ASM_MACROS_H
#define ASM_MACROS_H

// Stringify functions for use in inline assembly code:
#define STRINGIFY(x) #x
#define ASM_STRINGIFY(x) STRINGIFY(x)

// Calculates the virtual base address of a hardware module:
#define ASM_HW_ADDR(base)		(base + 0x80000000)

// Loads the base address of a hardware module into the specified register:
#define ASM_LOAD_BASE(reg, base) \
	"ldr " #reg ", =" ASM_STRINGIFY(ASM_HW_ADDR(base)) "\n\t"

#endif

