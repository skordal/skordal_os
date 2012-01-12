@ SkordalOS C Library
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
.syntax unified
.section .text

@ strcpy - Copies a string.
@ Arguments:
@	r0 = destination
@	r1 = source
@ Returns:
@	r0 = pointer to the destination string.
.global strcpy
strcpy:
	pld [r1]
	mov r2, r0

1:
	ldrb r3, [r1], #1
	strb r3, [r2], #1
	cmp r3, #0
	it ne
	bne 1b

	bx lr

@ strncpy - Copies a string with length restrictions.
@ Arguments:
@	r0 = destination
@	r1 = source
@	r2 = length
@ Returns:
@ 	r0 = pointer to the destination string.
.global strncpy
strncpy:
	push {v1, lr}
	pld [r1]
	mov r3, r0

1:
	ldrb v1, [r1], #1
	strb v1, [r3], #1
	cmp v1, #0
	it eq
	beq 2f

	subs r2, #1
	it ne
	bne 1b

2:
	pop {v1, pc}

