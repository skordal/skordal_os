@ SkordalOS Hello World Application
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
.section .text

#include "../../syscalls.h"

@ Application entry point.
.global start
start:
	mov r0, #1		@ stdout file descriptor
	ldr r1, =hello_message	@ message
	mov r2, #12		@ message length
	svc #SYSCALL_WRITE	@ write(1, hello_message, 12)

	svc #SYSCALL_EXIT	@ exits the application

.section .data
hello_message:
	.asciz "Hello world\n"

