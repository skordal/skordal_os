# SkordalOS Makefile
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include config.mk

# TODO: Fix dependency generation, to prevent rebuilds.
.PHONY: clean all apps libc
OBJECTS := \
	cpuid.o \
	debug.o \
	display.o \
	gpio.o \
	i2c.o \
	interrupts.o \
	irq.o \
	iva2.o \
	kernel.o \
	mm.o \
	mmu.o \
	pm.o \
	process.o \
	sd.o \
	spinlock.o \
	start.o \
	timer.o \
	tps65950.o

all: kernel #libc apps

kernel: $(OBJECTS) skordal_os.ld
	@make -C asm
	$(LD) $(LDFLAGS) -L asm -L libc -o skordal_os.elf -T skordal_os.ld \
		$(OBJECTS) -lasm_functions
	$(OBJCOPY) -S -O binary -j .text -j .data skordal_os.elf skordal_os.bin
	$(MKIMAGE) -A arm -O linux -T kernel -C none -a 0x80008000 \
		-e 0x80008000 -n SkordalOS -d skordal_os.bin uImage

apps: libc
	@make -C apps

libc:
	@make -C libc

clean:
	@make -C asm clean
	@make -C apps clean
	@make -C libc clean
	-$(RM) $(OBJECTS)
	-$(RM) skordal_os.bin skordal_os.elf uImage

# The totally-clean target also searches for swap files and deletes them:
totally-clean: clean
	find . -name \*.o | xargs rm -vf
	find . -name .\*.swp | xargs rm -vf

# Object file targets:
# TODO: Make automagic targets with dependency tracking :-)

cpuid.o: cpuid.c cpuid.h
	$(CC) $(CFLAGS) -c cpuid.c -o cpuid.o

data_abort.o: data_abort.S
	$(CC) $(CFLAGS) -c data_abort.S -o data_abort.o

debug.o: debug.c debug.h
	$(CC) $(CFLAGS) -c debug.c -o debug.o

display.o: display.c display.h
	$(CC) $(CFLAGS) -c display.c -o display.o

gpio.o: gpio.c gpio.h
	$(CC) $(CFLAGS) -c gpio.c -o gpio.o

i2c.o: i2c.c i2c.h
	$(CC) $(CFLAGS) -c i2c.c -o i2c.o

interrupts.o: interrupts.S
	$(CC) $(CFLAGS) -c interrupts.S -o interrupts.o

irq.o: irq.c irq.h
	$(CC) $(CFLAGS) -c irq.c -o irq.o

iva2.o: iva2.c iva2.h
	$(CC) $(CFLAGS) -c iva2.c -o iva2.o

kernel.o: kernel.c kernel.h
	$(CC) $(CFLAGS) -c kernel.c -o kernel.o

mmu.o: mmu.c mmu.h types.h hardware/mmu.h
	$(CC) $(CFLAGS) -c mmu.c -o mmu.o

mm.o: mm.c mm.h
	$(CC) $(CFLAGS) -c mm.c -o mm.o

pm.o: pm.c pm.h
	$(CC) $(CFLAGS) -c pm.c -o pm.o

process.o: process.c process.h
	$(CC) $(CFLAGS) -c process.c -o process.o

sd.o: sd.c sd.h
	$(CC) $(CFLAGS) -c sd.c -o sd.o

spinlock.o: spinlock.S spinlock.h
	$(CC) $(CFLAGS) -c spinlock.S -o spinlock.o

start.o: start.S
	$(CC) $(CFLAGS) -c start.S -o start.o

timer.o: timer.c timer.h
	$(CC) $(CFLAGS) -c timer.c -o timer.o

tps65950.o: tps65950.c tps65950.h
	$(CC) $(CFLAGS) -c tps65950.c -o tps65950.o

