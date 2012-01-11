// SkordalOS: DM37x UART Bitfield Details
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef HARDWARE_UART_H
#define HARDWARE_UART_H

// UART modules base addresses:
#define UART0_BASE	0x4806a000
#define UART1_BASE	0x4806c000
#define UART2_BASE	0x49020000
#define UART3_BASE	0x49042000

// UART address space size:
#define UART_SPACE_SIZE	4096

// UART register offsets:
#define UART_THR_REG	0x00
#define UART_LSR_REG	0x14

// Register bitfield names:
#define UART_LSR_TX_FIFO_E	(1 << 5)

#endif

