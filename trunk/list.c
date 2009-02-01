#include <stdlib.h>
#include "list.h"


/* malloc a new list header,  initialize it, and return its address */

list_t *list_init(
void)
{
	list_t *newlist;

	newlist = (list_t *)malloc(sizeof(list_t));

	newlist->head = NULL;
	newlist->tail = NULL;

	return newlist;
}

/* Add an element to the end of a list */

void list_add(
list_t *list,
void   *entity)
{
	link_t *newlink = (link_t *)malloc(sizeof(link_t));
	newlink->next = NULL;
	newlink->item = entity;

	if(list->head == NULL) {
		list->head = newlink;
		list->tail = newlink;
	} else {
		list->tail->next = newlink;
		list->tail = newlink;
	}
}


/* Free all of the list control structures and   */
/* the entities they control                     */

void list_del(
list_t *list)
{
	link_t *templink;

	while(list->head != NULL)
	{
		templink = list->head;
		list->head = list->head->next;
		free(templink->item);
		free(templink);
	}

	free(list);
}
