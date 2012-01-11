# SkordalOS C library
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include ../config.mk
.PHONY: all clean

# Objects to build:
OBJECT_FILES := \
	memset.o \
	strcpy.o \
	strlen.o

# Main build target, builds the entire C library:
all: copyfiles $(OBJECT_FILES)
	$(AR) rcs libc.a $(OBJECT_FILES)
	$(RANLIB) libc.a

# Copies neccessary header files from the kernel directory:
copyfiles:
	$(MKDIR) -p include/sys
	$(CP) ../types.h include/sys

memset.o: memset.S
	$(CC) -c $(CFLAGS) -isystem include memset.S -o memset.o

strcpy.o: strcpy.S
	$(CC) -c $(CFLAGS) -isystem include strcpy.S -o strcpy.o

strlen.o: strlen.S
	$(CC) -c $(CFLAGS) -isystem include strlen.S -o strlen.o

clean:
	-$(RM) include/sys/types.h
	-$(RM) $(OBJECT_FILES)
	-$(RM) libc.a

