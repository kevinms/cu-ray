/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 9, 2009
 * Program 5
 *
 * Description
 * Creates a new list header, initializes it, and returns it's address
 ***********************************************************************/
 
/* list.c */

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

link_t::link_t(void *newentity)
{
   next = NULL;
   entity = newentity;
}

link_t::~link_t(void)
{
	printf("destroying link_t at %p \n", this);
}

void link_t::set_next(link_t *new_next)
{

/* set the next element of this link to new_next */
	next = new_next;
}


link_t * link_t::get_next()
{

/* return the next pointer of this link */

	return(next);
}

void * link_t::get_entity()
{

/* return the entity pointer of this link */
	return(entity);
}


list_t::list_t()
{

/* Set first, last, and current pointers to NULL */
	first = NULL;
	last = NULL;
	current = NULL;
}

list_t::~list_t(void)
{
	link_t *copy;
	while(first != NULL)
	{
		copy = first->get_next();
		delete first;
		first = copy;
	}
}

void list_t::add(void *entity)
{

/* Create a new link passing it the entity pointer */
   link_t *link;
   link = new link_t(entity);

/* Now add the link to the list using generally the */
/* same approach as the C version                   */
	if(first == NULL)
	{
		first = link;
		last = link;
	}
	else
	{
		last->set_next(link);
		last = link;
	}
	current = link;
}

void list_t::insert(void *newent)
{
	link_t *link;
	link_t *traverse;

	if(first == NULL)
		add(newent);
	else if(current == first)
	{
		link = new link_t(newent);
		current = link;
		link->set_next(first);
		first = link;
	}
	else
	{
		link = new link_t(newent);
		link->set_next(current);
		traverse = first;
		while(traverse->get_next() != current)
		{
			traverse = traverse->get_next();
		}
		traverse->set_next(link);
		current = link;
	}
}

void list_t::remove(void)
{	
	link_t *traverse;

	if (first == NULL)
	{
	}
	else if(first->get_next() == NULL)
	{
		delete first;
		first = NULL;
		last = NULL;
		current = NULL;
	}
	else if(current == first)
	{
		first = current->get_next();
		delete current;
		current = first;
	}
	else
	{
		traverse = first;
		while(traverse->get_next() != current)
		{
			traverse = traverse->get_next();
		}
		if(current == last)
			last = traverse;
		traverse->set_next(current->get_next());
		delete current;
		current = traverse;
	}
}

void * list_t::start(void)
{

/* Set the current link pointer to the first pointer. */
	current = first;

/* If the list is not empty return the entity pointed */
/* to by the current/first link pointer               */
	if(first == NULL)
	{
		return(NULL);
	}
	return( current->get_entity() );
}

void * list_t::get_next(void)
{
	link_t *link;


/* Set link to the next pointer of the current link */
	link = current->get_next();


/* If the value of link is NULL  return NULL */
	if(link == NULL)
	{
		return(NULL);
	}


/* Otherwise set current to link and return a pointer */
/* to the entity pointed to by link                   */
	else
	{
		current = link;
		return( current->get_entity() );
	}

}


