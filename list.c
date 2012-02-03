// SkordalOS Linked List Implementation
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include "list.h"

// Allocates a new list:
list_t * list_new()
{
	list_t * retval = mm_alloc(sizeof(list_t), 4);
	zero_mem_4(retval, sizeof(retval));
	return retval;
}

// Frees a previously allocated list:
void list_free(list_t * list)
{
	list_rewind(list);
	while(list->current != NULL)
	{
		list_node_t * temp = list->current;
		list->current = list->current->next;
		mm_free(temp);
	}

	mm_free(list);
}

// Appends an object to the end of the list:
void list_append(list_t * list, void * data)
{
	list_node_t * new_node = mm_alloc(sizeof(list_node_t), 4);
	new_node->data = data;

	if(list->last == NULL)
	{
		list->first = new_node;
		list->last = new_node;
		list->current = new_node;
	} else {
		new_node->prev = list->last;
		list->last->next = new_node;
		list->last = new_node;
	}

	++list->num_elements;
}

// Prepends an object to the beginning of the list:
void list_prepend(list_t * list, void * data)
{
	list_node_t * new_node = mm_alloc(sizeof(list_node_t), 4);
	new_node->data = data;

	if(list->first == NULL)
	{
		list->first = new_node;
		list->last = new_node;
		list->current = new_node;
	} else {
		new_node->next = list->first;
		list->first->prev = new_node;
		list->first = new_node;
	}

	++list->num_elements;
}

// Advances the list one position:
bool list_advance(list_t * list)
{
	if(list->current == NULL || list->current->next == NULL)
		return false;
	list->current = list->current->next;
	return true;
}

// Decreases the list one position:
bool list_decrease(list_t * list)
{
	if(list->current == NULL || list->current->prev == NULL)
		return false;
	list->current = list->current->prev;
	return true;
}

// Rewinds the current list position to the start of the list:
void list_rewind(list_t * list)
{
	list->current = list->first;	
}

// Fast-forwards the list to the end:
void list_fast_forward(list_t * list)
{
	list->current = list->last;
}

// Gets the current element in the list:
void * list_get_element(list_t * list)
{
	if(list->current == NULL)
		return NULL;
	else
		return list->current->data;
}

// Gets the current number of elements:
size_t list_get_num_elements(list_t * list)
{
	return list->num_elements;
}

// Returns true if the list is empty:
bool list_is_empty(list_t * list)
{
	return list_get_num_elements(list) == 0;
}

// Removes an element from the list:
void * list_remove(list_t * list)
{
	if(list_is_empty(list) || list->current == NULL)
		return NULL;
	
	list_node_t * current_node = list->current;
	void * retval = current_node->data;

	if(current_node->prev == NULL)
		list->first = current_node->next;
	else
		current_node->prev->next = current_node->next;

	if(current_node->next == NULL)
		list->last = current_node->prev;
	else
		current_node->next->prev = current_node->prev;

	if(current_node->next != NULL)
		list->current = current_node->next;
	else
		list->current = current_node->prev;

	--list->num_elements;
	mm_free(current_node);

	return retval;
}

