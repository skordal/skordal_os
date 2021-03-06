@ SkordalOS C Library
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
.syntax unified
.section .text

@ Fills a memory area with a specified amount of a constant byte.
@ Arguments:
@	r0 = pointer to memory area.
@	r1 = constant byte to use.
@	r2 = length of memory area.
@ Returns:
@	r0 = pointer to the memory area.
.global memset
memset:
	mov r3, r0

1:
	str r1, [r3], #1
	subs r2, #1
	it ne
	bne 1b

	bx lr

