@ SkordalOS C Library
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

@ memcpy - Copies memory from source to destination.
@ Arguments:
@	r0 = destination
@	r1 = source
@	r2 = length
@ Returns:
@	r0 = pointer to the destination string.
.global memcpy
memcpy:
	push {r4, lr}

	pld [r1]
	mov r3, r0
1:
	ldrb v1, [r1], #1
	strb v1, [r3], #1
	subs r2, #1
	bne 1b

	pop {r4, pc}

@ mempcpy - Copies memory from source to destination.
@ Arguments:
@	r0 = destination
@	r1 = source
@ 	r2 = length
@ Returns:
@	r0 = pointer to the byte after the copied data.
.global mempcpy
mempcpy:
	pld [r1]
1:
	ldrb r3, [r1], #1
	strb r3, [r0], #1
	subs r2, #1
	bne 1b

	mov pc, lr

