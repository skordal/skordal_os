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
	mov pc, lr

@ mempcpy - Copies memory from source to destination.
@ Arguments:
@	r0 = destination
@	r1 = source
@ 	r2 = length
@ Returns:
@	r0 = pointer to the byte after the copied data.
.global mempcpy
mempcpy:
	mov pc, lr

