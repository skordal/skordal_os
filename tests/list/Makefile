# SkordalOS Linked List Test Makefile
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include ../../config.mk

.PHONY: all clean

all: list_test.c
	$(CP) -f ../../list.{h,c} .
	$(SED) -i '/#include/d' list.h
	$(TEST_CC) -include ../test_support.h $(TEST_CFLAGS) list_test.c list.c -o list_test -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast
	./list_test

clean:
	$(RM) list.h list.c list_test

