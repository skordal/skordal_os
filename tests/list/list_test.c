// SkordalOS Linked List Test Application
// (c) Kristian K. Skordal 2011 - 2012 <kristian.skordal@gmail.com>

#include <stdio.h>
#include "list.h"

int main(int argc, char * argv[])
{
	list_t * test_list;

	// Create list:
	printf("Testing linked list implementation:\n");
	printf("\tCreating list: ");
	test_list = list_new();
	printf("ok\n");

	// Append 10 integers:
	printf("\tAppending 10 elements: ");
	for(int i = 0; i < 10; ++i)
	{
		list_append(test_list, (void *) i);
		printf("%d ", i);
	}
	printf("ok\n");

	// Check if the size of the list is correct:
	printf("\tChecking current size of list: ");
	if(list_get_num_elements(test_list) != 10)
		printf("failed!\n");
	else
		printf("ok\n");

	// Verify that all the objects in the list have been added and are
	// in the correct sequence:
	printf("\tVerifying list contents: ");
	list_rewind(test_list);
	for(int i = 0; i < 10; ++i)
	{
		void * data = list_get_element(test_list);
		if((int) data != i)
		{
			printf("failed!\t(invalid element)\n");
			break;
		}
		printf("%d ", (int) data);

		if(!list_advance(test_list) && i < 9)
		{
			printf("failed!\t(end of list reached)\n");
			break;
		}
	}
	printf("ok\n");

	// Delete all list elements:
	printf("\tDeleting all elements: ");
//	list_rewind(test_list);
//	while(!list_is_empty(test_list))
//	{
//		printf("%d ", (int) list_remove(test_list));
//		if(test_list->current == NULL)
//			break;
//	}
	printf("not implemented\n");

	// Test prepending elements:
	printf("\tPrepending 10 elements: ");
	for(int i = 0; i < 10; ++i)
	{
		list_prepend(test_list, (void *) i);
		printf("%d ", i);
	}
	printf("ok\n");

	// Verify the prepended elements:
	printf("\tVerifying elements: ");
	list_rewind(test_list);
	for(int i = 9; i >= 0; --i)
	{
		void * data = list_get_element(test_list);
		if((int) data != i)
		{
			printf("failed!\t(invalid element)\n");
			break;
		}
		printf("%d ", (int) data);

		if(!list_advance(test_list) && i > 0)
		{
			printf("failed!\t(end of list reached)\n");
			break;
		}
	}
	printf("ok\n");

	// Free the list:
	printf("\tFreeing list: ");
	list_free(test_list);
	printf("ok\n");

	return 0;
}

