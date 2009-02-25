/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * February 24, 2009
 * Program 4
 *
 * Description
 * Basic functions for the ray system, such as finding the closest
 * object and tracing the ray from the camera to that object.
 ***********************************************************************/

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

/**/
/* This function traces a single ray and returns the  */
/* composite intensity of the light it encounters     */
void ray_trace(
model_t *model,
vec_t    *base,        /* location of viewer or previous hit */
vec_t    *dir,         /* unit vector in direction of object */
drgb_t   *dpix,        /* pixel     return location */
double   total_dist,   /* distance ray has traveled so far */
object_t *last_hit)    /* most recently hit object */
{
	object_t *closest;
	double   mindist;
	drgb_t   thisray = {0.0, 0.0, 0.0};

	closest = find_closest_object(model->objs, base, dir, NULL, &mindist);
	if(closest != NULL)
	{
		#ifdef DBG_HIT
			fprintf(stderr, "%-12s HIT:(%5.1lf, %5.1lf, %5.1lf)",
				closest->objname,
				closest->hitloc.x, closest->hitloc.y,
				closest->hitloc.z);
		#endif

		closest->getamb(closest, &thisray);
	}

	drgb_scale(1.0/mindist, &thisray, &thisray);
	drgb_sum(&thisray, dpix, dpix);

	#ifdef DBG_DRGB
		fprintf(stderr, "%-12s DRGB:(%5.2lf, %5.2lf, %5.2lf)",
			closest->objname, pix->r, pix->g, pix->b);
	#endif
}
