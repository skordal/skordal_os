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
	new_node->next = NULL;
	new_node->data = data;

	if(list->last == NULL)
	{
		list->first = new_node;
		list->last = new_node;
		list->current = new_node;
	} else {
		list->last->next = new_node;
		list->last = new_node;
	}

	++list->num_elements;
}

// Prepends an object to the beginning of the list:
void list_prepend(list_t * list, void * data)
{
	list_node_t * new_node = mm_alloc(sizeof(list_node_t), 4);
	new_node->next = NULL;
	new_node->data = data;

	if(list->first == NULL)
	{
		list->first = new_node;
		list->last = new_node;
		list->current = new_node;
	} else {
		new_node->next = list->first;
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

// Gets the current element in the list:
void * list_get_element(list_t * list)
{
	if(list->current == NULL)
		return NULL;
	else
		return list->current->data;
}

