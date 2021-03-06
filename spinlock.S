@ SkordalOS Spinlocks
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
.section .text
.align 4

@ Locks a spinlock.
@ Arguments:
@ 	r0 = pointer to spinlock
.global spinlock_lock
spinlock_lock:
	mvn r2, #0
1:	@ BIG TODO: These functions should use the ldrex/strex, but these cause data aborts!
	ldr r1, [r0]
@	ldrex r1, [r0]
	cmp r1, #0
	streq r2, [r0]
@	strexeq r1, r2, [r0]
@	cmpeq r1, #0
	yieldne
	bne 1b

	bx lr

@ Checks if a spinlock is locked:
@ Arguments:
@ 	r0 = pointer to spinlock.
@ Returns:
@	r0 = 1 if spinlock os locked.
.global spinlock_is_locked
spinlock_is_locked:
	ldr r1, [r0]
	cmp r1, #0
	moveq r0, #0
	movne r0, #1
	bx lr

@ Unlocks a spinlock.
@ Arguments:
@	r0 = pointer to spinlock
.global spinlock_unlock
spinlock_unlock:
	mov r1, #0
	str r1, [r0]
	bx lr
