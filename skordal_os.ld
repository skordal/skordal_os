/*                     SkordalOS - Linker Script                    */
/* (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com> */

SECTIONS
{
	app_stack_top = 0x80000000;

	ram_base = 0x80000000;
	stack_bottom = ram_base;
	stack_top = 0x80008000;

	.text 0x80008000 :
	{
		text_start = .;
		start.o(.text)
		*(.text*)
	}
	text_end = ALIGN(4096);

	.data : ALIGN(4096)
	{
		data_start = .;
		*(.data*)
		*(.rodata*)
	}

	.bss : ALIGN(4)
	{
		bss_start = .;
		*(.bss*)
	}
	bss_end = ALIGN(4);
	data_end = ALIGN(4096);

	data_page_end = data_end;
	kernel_stack_top = 0xa0000000;
}

