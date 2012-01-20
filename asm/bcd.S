@ SkordalOS BCD Utility Functions
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

@ Converts an 8-bit BCD number into a binary number.
@ Arguments:
@	r0 = 8-bit BCD number.
.global bcd2bin
bcd2bin:
	and r2, r0, #0x0f
	mov r1, #10
	lsr r0, #4
	mla r0, r0, r1, r2
	bx lr

