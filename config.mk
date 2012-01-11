# SkordalOS Makefile Configuration
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

# Build tools:
TOOL_PREFIX ?= arm-none-eabi
AR          := $(TOOL_PREFIX)-ar
CC          := $(TOOL_PREFIX)-gcc
LD          := $(TOOL_PREFIX)-ld
NM          := $(TOOL_PREFIX)-nm
OBJCOPY     := $(TOOL_PREFIX)-objcopy
RANLIB      := $(TOOL_PREFIX)-ranlib

# Other tools:
CP      ?= cp
FIND    ?= find
MKDIR   ?= mkdir
MKIMAGE ?= mkimage
RM      ?= rm

# Debug flags:
#CFLAGS += -DDEBUG_MM # Uncomment this line to debug the kernel memory manager.
#CFLAGS += -DDEBUG_MMU -DDEBUG_PAGETABLE # Uncomment this line to debug the MMU functions.
#CFLAGS += -DDEBUG_IRQ # Uncomment to debug the IRQ handling code.
#CFLAGS += -DDEBUG_GPIO # Uncomment this line to enable debugging the GPIO functions.

# Build flags:
CFLAGS += -mcpu=cortex-a8 -mtune=cortex-a8 -Wa,-mcpu=cortex-a8+sec -ffreestanding \
	-funsigned-bitfields -O2 -std=gnu99 -nostdinc -nostdlib -mfpu=neon -mhard-float \
	-isystem libc/include
LDFLAGS  += -nostdlib

