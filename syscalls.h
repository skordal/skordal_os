// SkordalOS System Call Numbers and Information
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef SYSCALLS_H
#define SYSCALLS_H

// Syscalls are called using the svc instruction from assembler code. The
// syscall number should be specified as parameter. Invalid syscall numbers
// whill result in the programme being terminated with SIGILL.

// The exit syscall, called at the end of programmes:
#define SYSCALL_EXIT	1
// The yield syscall, used to allow other programmes to run in this process'
// timeslot:
#define SYSCALL_YIELD	2

// UNIX syscall: open
#define SYSCALL_OPEN	3
// UNIX syscall: close
#define SYSCALL_CLOSE	4
// UNIX syscall: read
#define SYSCALL_READ	5
// UNIX syscall: write
#define SYSCALL_WRITE	6

#endif

