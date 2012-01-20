# Various Assembler Functions for SkordalOS: Makefile
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include ../config.mk

.PHONY: clean
OBJECT_FILES := bcd.o mask_left.o zero_mem.o

all: $(OBJECT_FILES) functions.h
	$(AR) rcs libasm_functions.a $(OBJECT_FILES)
	$(RANLIB) libasm_functions.a

bcd.o: bcd.S
	$(CC) $(CFLAGS) -c bcd.S -o bcd.o

mask_left.o: mask_left.S
	$(CC) $(CFLAGS) -c mask_left.S -o mask_left.o

zero_mem.o: zero_mem.S
	$(CC) $(CFLAGS) -c zero_mem.S -o zero_mem.o

clean:
	-$(RM) $(OBJECT_FILES)
	-$(RM) libasm_functions.a
