@ SkordalOS Mask Left Function
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

@ mask_left sets all the bits to the left of and including the leftmost
@ bit in the input argument.
@ Arguments:
@	r0 = bit to mask the left of.
.global mask_left
mask_left:
	clz r1, r0
	mvn r2, #0
	add r1, r1, #1
	mvn r0, r2, lsr r1
	bx lr


