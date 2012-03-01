// SkordalOS Linked List Implementation
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#ifndef LIST_H
#define LIST_H

#include "asm/functions.h"

#include "mm.h"
#include "types.h"

// TODO: Some of the functions here can be replaced by macros to save
//       space in the compiled file.

// List node structure:
typedef struct __list_node_t {
	struct __list_node_t * next, * prev;
	void * data;
} list_node_t;

// List structure:
typedef struct {
	list_node_t * first, * last, * current;
	size_t num_elements;
} list_t;

// Allocates a new linked list:
list_t * list_new() __attribute((warn_unused_result));
// Frees an allocated linked list:
void list_free(list_t * list);

// Appends an object to the end of a list:
void list_append(list_t * list, void * data);
// Prepends an object to the beginning of a list:
void list_prepend(list_t * list, void * data);

// Advances the current list position, returns false if at the end of the list:
bool list_advance(list_t * list);
// Decreases the current list position, returns false if at the beginning of the list:
bool list_decrease(list_t * list);
// Fast-forwards the list to the end:
#define list_fast_forward(list) list->current = list->last
// Rewinds the list to the beginning:
#define list_rewind(list) list->current = list->first

// Gets the element at the current list position:
void * list_get_element(list_t * list);
// Gets the current number of elements:
#define list_get_num_elements(list) list->num_elements

// Returns true if the list is empty:
#define list_is_empty(list) list_get_num_elements(list) == 0

// Returns true if the current position is at the beginning of the list:
bool list_at_beginning(list_t * list);
// Returns true if the current position is at the end of the list:
bool list_at_end(list_t * list);

// Deletes the element at the current list position, returns NULL if there
// are no elements left in the list (but also if the element at the current
// location actually was NULL, use list_at_end(l) or list_at_beginning(l)
// to be sure). The current pointer is set to the next element if possible,
// if not it is set to the previous.
void * list_remove(list_t * list);

#endif

