@ SkordalOS Interrupt Handling Code
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
.section .text

#include "hardware/intc.h"
#include "hardware/processor.h"

@ Initializes the interrupt handling code. This function
@ sets the VBAR register to point to the table of interrupt
@ handlers.
.global interrupts_init
interrupts_init:
	ldr r0, =interrupt_table
	mcr p15, 0, r0, c12, c0, 0
	cpsie if
	bx lr

@ Table of interrupt handlers.
.balign 32
interrupt_table:
	ldr pc, =start		@ Reset handler (not used)
	ldr pc, =undef		@ Undefined instruction
	ldr pc, =svc		@ Supervisor call
	ldr pc, =prefetch_abort	@ Prefetch abort
	ldr pc, =data_abort	@ Data abort
	movs pc, lr		@ Unused interrupt
	ldr pc, =irq		@ IRQ interrupt
	ldr pc, =fiq		@ FIQ interrupt
.ltorg

undef:
	b undef
	movs pc, lr

svc:
	push {r0 - r3, ip, lr}

	@ Get the system call number:
	tst lr, #1		@ Check if we were called from thumb code

	@ If not called from thumb code:
	ldrne r0, [lr, #-4]
	andne r0, #0x00ffffff
	bne 1f

	@ If called from thumb code:
	ldrh r0, [lr, #-2]
	and r0, #0x000000ff

1:
	push {r0}
	bl debug_print_dec
	bl debug_print_newline
	pop {r0}

	pop {r0 - r3, ip, lr}
	movs pc, lr

prefetch_abort:
	sub lr, #4
	srsdb sp!, #PROCESSOR_MODE_SVC
	cps #PROCESSOR_MODE_SVC
	push {r0 - r3, ip, lr}
	mov r0, #'P'
	bl debug_print_char
	pop {r0 - r3, ip, lr}
	rfeia sp! 

data_abort:
	sub lr, #4
	srsdb sp!, #PROCESSOR_MODE_SVC
	cps #PROCESSOR_MODE_SVC
	push {r0 - r3, ip, lr}
	mov r0, #'D'
	bl debug_print_char
	pop {r0 - r3, ip, lr}
	rfeia sp! 

irq:
	sub lr, #4
	srsdb #PROCESSOR_MODE_SVC!
	cps #PROCESSOR_MODE_SVC

	push {r0 - r3, ip, lr}
	bl irq_handler
	pop {r0 - r3, ip, lr}

	rfeia sp!

fiq:
	mov ip, lr

	@ Get the FIQ number to process:
	ldr r8, =INTC_BASE + 0x80000000
	ldr r9, [r8, #INTC_SIR_FIQ]
	and r8, r9, #0x7f

1:
	@ Reset the interrupt status:
	dsb
	ldr r8, =INTC_BASE + 0x80000000
	mov r9, #2
	dsb
	str r9, [r8, #INTC_CONTROL]

	mov lr, ip
	subs pc, lr, #4

