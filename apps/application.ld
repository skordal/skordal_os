/*************************************************************/
/*         Linker Script for SkordalOS Applications          */
/* (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com> */
/*************************************************************/

SECTIONS
{
	.text :
	{
		../header.o(.text)
		*(.text*)
	}

	data_start = ALIGN(4096); . = data_start;
	.data :
	{
		*(.data*)
	}

	bss_start = ALIGN(4096); . = bss_start;
	.bss :
	{
		*(.bss*)
	}
	application_end = ALIGN(4096);
}

