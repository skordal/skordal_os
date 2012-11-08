@ SkordalOS Start File
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
.section .text

#include "hardware/processor.h"
#include "hardware/sctlr.h"

@ This is the kernel entry point.
.global start
start:
	@ Set up a temporary stack until the MMU has been initialized:
	ldr sp, =0x80008000

	@ Zero the .bss section:
	ldr r0, =bss_start
	ldr r1, =bss_end
	eor r2, r2, r2
1:
	cmp r0, r1
	strne r2, [r0], #4
	bne 1b

	@ Clear the local monitor to prevent faults when using spinlocks:
	clrex

	@ Enable neon and vfp instructions:
	mov r0, #CPACR_FULL_ACCESS << CPACR_COPROC(10)|CPACR_FULL_ACCESS << CPACR_COPROC(11)
	mcr p15, 0, r0, c1, c0, 2
	isb

	vmrs r0, FPEXC
	orr r0, #(1 << 30)
	vmsr FPEXC, r0

	@ Print a short message to show we are working:
	ldr r0, =boot_message
	bl debug_print_string
	bl debug_print_newline
	bl debug_print_newline

	@ Set up the kernel memory manager. This also initializes the MMU.
	bl mm_init

	@ Enable the MMU, caches and branch prediction:
	mrc p15, 0, r0, c1, c0, 0
	ldr r1, =(SCTLR_M|SCTLR_C|SCTLR_Z|SCTLR_I)
	orr r0, r0, r1
	mcr p15, 0, r0, c1, c0, 0

	@ Set the new stack pointer:
	ldr sp, =kernel_stack_top	@ kernel stack

	@ Set up interrupt handlers:
	bl interrupts_init

	@ Initialize the kernel:
	bl kernel_init

	@ Run the kernel main loop:
	bl kernel_main

loopy:	@ A little loop here, in case the kernel main function should return
	@ by accident.
	wfi
	b loopy

.section .rodata
boot_message:
	.asciz "SkordalOS booting..."

