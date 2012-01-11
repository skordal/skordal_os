@ SkordalOS C Library
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
.section .text

@ strlen - measures string length.
@ Arguments:
@	r0 = pointer to the string to be measured.
@ Returns:
@	r0 = length of string.
.global strlen
strlen:
	pld [r0]		@ Preload the string, if possible.
	mov r1, #0		@ Use r1 for counting.

1:
	ldrb r2, [r0], #1	@ Load byte from string.
	cmp r2, #0		@ Check for end-of-string zero.
	addne r1, #1		@ Add one to counter if not.
	bne 1b

	mov r0, r1
	bx lr

