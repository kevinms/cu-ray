#include "ray.h"

object_t *find_closest_object(
list_t   *list,        /* Model structure               */
vec_t    *base,        /* Base of ray (viewpoint)       */
vec_t    *dir,         /* unit direction of ray         */
object_t *last_hit,    /* object last hit (ignore)      */
double   *retdist)     /* return dist to hit point here */
{
    object_t *minobj = NULL;
    double    mindist = -1.0;

	link_t *link = NULL;
	object_t *obj = NULL;
	double dist;
	
	link = (link_t *)list->head;
	
	while( link != NULL )
	{
		obj = (object_t *)link->item;
		dist = obj->hits(base, dir, obj);
		if (dist != -1 && mindist == -1)
		{
			mindist=dist;
			minobj=obj;
		}
		else if(dist != -1 && dist < mindist)
		{
			mindist = dist;
			minobj=obj;
		}
		link = link->next;
	}

	*retdist = mindist;	
    return(minobj);
}
