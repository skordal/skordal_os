# SkordalOS Applications
# (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
include ../config.mk
.PHONY: all clean

# Applications to build:
APPLICATIONS := hello
.PHONY: $(APPLICATIONS)

all: application.ld header.o $(APPLICATIONS)

$(APPLICATIONS):
	@$(MAKE) -C $@

header.o: header.S
	$(CC) -c $(CFLAGS) header.S -o header.o

clean:
	$(RM) header.o
	for dir in $(APPLICATIONS); do \
		$(MAKE) -C $$dir clean; \
	done

