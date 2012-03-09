# SkordalOS C library
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include ../config.mk
.PHONY: all clean

SOURCE_FILES :=
ASSEMBLER_FILES := \
	memset.S \
	strcpy.S \
	strlen.S

OBJECT_FILES := $(SOURCE_FILES:.c=.o) $(ASSEMBLER_FILES:.S=.o)

# Main build target, builds the entire C library:
all: copyfiles $(OBJECT_FILES)
	$(AR) rcs libc.a $(OBJECT_FILES)
	$(RANLIB) libc.a

# Copies neccessary header files from the kernel directory:
copyfiles:
	$(MKDIR) -p include/sys
	$(CP) ../types.h include/sys

clean:
	-$(RM) include/sys/types.h
	-$(RM) $(OBJECT_FILES)
	-$(RM) libc.a

%.o: %.S
	$(CC) $(CFLAGS) -c -isystem include $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -isystem include $< -o $@

