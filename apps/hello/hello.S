@ SkordalOS Hello World Application
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>
.section .text

@ Application entry point.
.global start
start:
	@ TODO: Fill in when syscalls have been implemented.

.section .data
hello_message:
	.asciz "Hello world\n"

