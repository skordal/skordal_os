# Various Assembler Functions for SkordalOS: Makefile
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include ../config.mk

.PHONY: clean

SOURCE_FILES := mask_left.S zero_mem.S
OBJECT_FILES := $(SOURCE_FILES:.S=.o)

all: $(OBJECT_FILES) functions.h
	$(AR) rcs libasm_functions.a $(OBJECT_FILES)
	$(RANLIB) libasm_functions.a

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-$(RM) $(OBJECT_FILES)
	-$(RM) libasm_functions.a
