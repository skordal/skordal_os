@ SkordalOS Spinlocks
@ (c) Kristian K. Skordal 2011 - 2012 - 2012
.section .text
.align 4

@ Locks a spinlock.
@ Arguments:
@ 	r0 = pointer to spinlock
.global spinlock_lock
spinlock_lock:
	mvn r2, #0
1:	@ BIG TODO: These functions should use the ldrex/strex, but these cause
	@           data aborts. This should be investigated later, but for now,
	@           this should work.
	ldr r1, [r0]
@	ldrex r1, [r0]
	cmp r1, #0
	streq r2, [r0]
@	strexeq r1, r2, [r0]
@	cmpeq r1, #0
	bne 1b

	bx lr

@ Unlocks a spinlock.
@ Arguments:
@	r0 = pointer to spinlock
.global spinlock_unlock
spinlock_unlock:
//	mvn r1, #0
//	str r1, [r0]
//	mov pc, lr
	bx lr
