@ SkordalOS Memory Move Function
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

@ Moves memory of length n from the source to the destination:
@	r0 = destination pointer
@	r1 = source pointer
@	r2 = length of block
.global memmove
memmove:
	push {v1, lr}

	pld [r1]
	ldr r3, =0

1:
	cmp r3, r2
	beq 2f

	ldrb v1, [r1, r3]
	strb v1, [r0, r3]
	add r3, #1
	b 1b

2:
	pop {v1, pc}

