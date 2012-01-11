@ SkordalOS Application Header
@ (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

@ The header is placed at the start of the text section.
.section .text

.align 4
sos_header:
	.4byte	start
	.byte 'S', 'O', 'S', 1
	.4byte data_start
	.4byte bss_start
	.4byte application_end

