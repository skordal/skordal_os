@ SkordalOS Interrupt Handling Code
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
.section .text

#include "hardware/intc.h"
#include "hardware/processor.h"

@ Number of the process switching FIQ:
@ TODO: Find a way of making this dependent of the timer used.
#define PROCESS_SWITCH_FIQ	37

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
	mov pc, #0		@ Reset handler (not used)
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
	push {r0 - r3, r12, lr}

	@ Get the system call number:
	ldr r0, [lr, #-4]
	and r0, #0x00ffffff

	push {r0}
	bl debug_print_dec
	bl debug_print_newline
	pop {r0}

	cmp r0, #1
1:
	wfieq
	beq 1b

	pop {r0 - r3, r12, lr}
	movs pc, lr

prefetch_abort:
	sub lr, #4
	srsdb sp!, #PROCESSOR_MODE_SVC
	cps #PROCESSOR_MODE_SVC
	push {r0 - r3, r12, lr}
	mov r0, #'P'
	bl debug_print_char
	pop {r0 - r3, r12, lr}
	rfeia sp! 

data_abort:
	sub lr, #4
	srsdb sp!, #PROCESSOR_MODE_SVC
	cps #PROCESSOR_MODE_SVC
	push {r0 - r3, r12, lr}
	mov r0, #'D'
	bl debug_print_char
	pop {r0 - r3, r12, lr}
	rfeia sp! 

irq:
	sub lr, #4
	srsdb #PROCESSOR_MODE_SVC!
	cps #PROCESSOR_MODE_SVC

	@ Store user registers:
	stmdb sp, {r0 - lr}^
	sub sp, #15*4
	mrs r0, spsr
	push {r0, lr}

	@ Save the pointer to the user registers:
	mov r0, sp
	ldr r1, =user_registers
	str r0, [r1]

	bl irq_handler

	@ Restore user registers from the user register pointer:
	ldr r0, =user_registers
	ldr r0, [r0]
	ldmia r0!, {r1, lr}
	msr spsr, r1
	ldmia r0, {r0 - lr}^

	@ Restore the stack pointer:
	add sp, #17*4

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
	str r9, [r8, #INTC_CONTROL]
	dsb

	mov lr, ip
	subs pc, lr, #4

.section .bss

@ The address of the user mode registers is stored here upon entry
@ to the IRQ handler. This is used by the process switching handler.
.global user_registers
user_registers:
	.skip 4

