# SkordalOS Hello World Application Makefile
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include ../../config.mk
.PHONY: all clean

all: hello.o
	$(LD) $(LDFLAGS) -T ../application.ld -o hello.elf hello.o
	$(OBJCOPY) -O binary -j .text -j .data hello.elf hello

hello.o: hello.S
	$(CC) -c $(CFLAGS) hello.S -o hello.o

clean:
	$(RM) hello.o hello.elf hello

