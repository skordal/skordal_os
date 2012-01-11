// SkordalOS Data Types
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef TYPES_H
#define TYPES_H

// NULL:
#ifndef NULL
#	define NULL 0
#endif

// Unsigned types:
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned long  uint64_t;

// Size types (32 bit):
typedef unsigned int   size_t;
typedef signed   int   ssize_t;

// Boolean:
typedef int bool;

// GID/UID types:
typedef uint32_t	uid_t;
typedef uint32_t	gid_t;

// PID type:
typedef uint8_t		pid_t;

// True/False:
#ifndef true
#	define true 1
#endif
#ifndef false
#	define false 0
#endif

#endif

