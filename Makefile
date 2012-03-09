# SkordalOS Makefile
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include config.mk

# TODO: Fix dependency generation, to prevent rebuilds.
.PHONY: clean all apps libc tests

SOURCE_FILES := \
	debug.c \
	gpio.c \
	i2c.c \
	irq.c \
	kernel.c \
	list.c \
	mm.c \
	mmu.c \
	pm.c \
	sd.c \
	timer.c \
	tps65950.c

ASSEMBLER_FILES := \
	interrupts.S \
	start.S \
	spinlock.S 

# Object files to be built:
OBJECTS := $(SOURCE_FILES:.c=.o) $(ASSEMBLER_FILES:.S=.o)

all: kernel # tests # libc apps

kernel: $(OBJECTS) skordal_os.ld
	@$(MAKE) -C asm
	$(LD) $(LDFLAGS) -L asm -L libc -o skordal_os.elf -T skordal_os.ld \
		$(OBJECTS) -lasm_functions
	$(OBJCOPY) -S -O binary -j .text -j .data skordal_os.elf skordal_os.bin
	$(MKIMAGE) -A arm -O linux -T kernel -C none -a 0x80008000 \
		-e 0x80008000 -n SkordalOS -d skordal_os.bin uImage

apps: libc
	@$(MAKE) -C apps

libc:
	@$(MAKE) -C libc

tests:
	@$(MAKE) -C tests

clean:
	@$(MAKE) -C asm clean
	@$(MAKE) -C apps clean
	@$(MAKE) -C libc clean
	@$(MAKE) -C tests clean
	-$(RM) $(OBJECTS)
	-$(RM) skordal_os.bin skordal_os.elf uImage

# The totally-clean target also searches for swap files and deletes them:
totally-clean: clean
	$(FIND) . -name \*.o | $(XARGS) $(RM) -vf
	$(FIND) . -name .\*.swp | $(XARGS) $(RM) -vf

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

