// SkordalOS Spinlocks
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef SPINLOCK_H
#define SPINLOCK_H

#include "types.h"

// Spinlock type:
typedef uint32_t spinlock_t;

// Locks a spinlock or waits for it to be ready:
void spinlock_lock(spinlock_t * lock);

// Checks if a spinlock is locked:
bool spinlock_is_locked(spinlock_t * lock);

// Unlocks a spinlock:
void spinlock_unlock(spinlock_t * lock);

#endif

