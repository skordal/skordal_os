/*                 SkordalOS - Linker Script                 */
/* (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com> */

SECTIONS
{
	app_stack_top = 0x80000000;

	ram_base = 0x80000000;
	stack_bottom = ram_base; . = stack_bottom;
	stack_top = 0x80008000; . = stack_top;

	text_start = .;
	.text :
	{
		start.o(.text)
		*(.text*)
	}

	data_start = ALIGN(4096); . = data_start;
	text_end = data_start;
	.data :
	{
		*(.data*)
		*(.rodata*)
	}

	bss_start = ALIGN(4); . = bss_start;
	.bss :
	{
		*(.bss*)
	}
	bss_end = ALIGN(4); . = bss_end;
	data_end = .;

	data_page_end = ALIGN(4096);
	kernel_stack_top = 0xa0000000;
}

