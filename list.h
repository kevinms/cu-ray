/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * February 24, 2009
 * Program 4
 *
 * Description
 * List structures
 ***********************************************************************/

typedef struct link_type
{
   struct link_type *next;    /* Next link in the list   */
   void             *item;    /* Item owned by this link */
}  link_t;

typedef struct list_type
{
   link_t  *head;             /* First link in the list */
   link_t  *tail;             /* Last link in the list  */
}  list_t;

/* Prototypes for list management functions */
/* malloc a new list header and initialize it */

list_t *list_init(
void);

/* Add an element to the end of a list */

void list_add(
list_t *list,
void   *entity);

/* Delete all of the list control structures and */
/* the entities they control                     */

void list_del(
list_t *list);

