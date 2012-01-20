@ SkordalOS Zero Memory Function
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

@ Zeroes out memory starting at the specified address and continuing for the
@ specified length.
@ Arguments:
@ 	r0 = start address
@	r1 = length
.global zero_mem
zero_mem:
	add r1, r0, r1
	eor r2, r2, r2
1:
	strb r2, [r0], #1
	cmp r0, r1
	bne 1b

	bx lr

@ Does the same as the above function, but works only on addresses and lengths
@ aligned to 4.
@ Arguments:
@	r0 = start address
@	r1 = length
.global zero_mem_4
zero_mem_4:
	add r1, r0, r1
	eor r2, r2, r2
1:
	str r2, [r0], #4
	cmp r0, r1
	bne 1b

	bx lr

