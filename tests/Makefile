# SkordalOS Architecture Independent Tests Makefile
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include ../config.mk

.PHONY: all clean

# List of test programmes to run:
TESTS ?= list
.PHONY: $(TESTS)

all: $(TESTS)

$(TESTS):
	@$(MAKE) -C $@

clean:
	for dir in $(TESTS); do \
		$(MAKE) -C $$dir clean; \
	done

