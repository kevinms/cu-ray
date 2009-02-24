/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * February 24, 2009
 * Program 4
 *
 * Description
 * This program alocates memory for a plane structure and parses and
 * loads the data for the structure.  Also a plane_dump() function.
 ***********************************************************************/

#include "ray.h"

static char *pln_attrs[] = { "point", "normal" };
#define NUM_ATTRS (sizeof(pln_attrs) / sizeof(char *))

static inline void pln_load_point(FILE *in, plane_t *pln)
{
   int count;
   count = fscanf(in, "%lf %lf %lf", &pln->point.x, 
					&pln->point.y, &pln->point.z);
/* ensure that the required number of values were found */
   assert(count == 3);
}

static inline void pln_load_normal(FILE *in, plane_t *pln)
{
   int count;
   count = fscanf(in, "%lf %lf %lf", &pln->normal.x, 
					&pln->normal.y, &pln->normal.z);
/* ensure that the required number of values were found */
   assert(count == 3);
}

static int plane_attr_load(
FILE      *in,
plane_t *pln,       /* material to be filled in */
char      *attrname)
{
	int ndx;

	ndx = table_lookup(pln_attrs, NUM_ATTRS, attrname);
	assert(ndx >= 0);
	switch(ndx)
	{
		case 0:
			pln_load_point(in, pln); return 0;
		case 1:
			pln_load_normal(in, pln); return 0;
		default:
			return -1;
	}
}

object_t *plane_init(
FILE *in,
model_t *model,
int attrmax)
{
    char attrname[NAME_LEN];
    int count;
	int attrp = 0;
	
	plane_t *pln;
	object_t *obj;
	obj = object_init(in, model);
	pln = (plane_t *)malloc(sizeof(plane_t));
	assert(pln != NULL);
	memset(pln, 0, sizeof(pln));

	count = fscanf(in, "%s", attrname);
	assert(count == 1 && attrname[0] != '}');

	while( (count == 1) && (attrname[0] != '}') )
	{
		assert(plane_attr_load(in, pln, attrname) == 0);
		*attrname = 0;
		attrp++;
		if(attrmax == 2 && attrp == 2)
		{
			break;
		}
		fscanf(in, "%s", attrname);
	}
	if(attrmax == 0)
	{
		assert(attrname[0] == '}');
	}
	obj->priv = (void *)pln;
	sprintf(obj->objtype, "plane");
	obj->dumper = plane_dump;
	obj->hits = plane_hits;
	
	
	return obj;
}

void plane_dump(
FILE *out,
object_t *obj)
{
	plane_t *pln;
	pln = (plane_t *)obj->priv;
        fprintf(stderr, "normal %11.1lf %5.1lf %5.1lf \n",
                        pln->normal.x, 
                        pln->normal.y, 
                        pln->normal.z);
						
        fprintf(stderr, "point %12.1lf %5.1lf %5.1lf \n\n",
                        pln->point.x, 
                        pln->point.y, 
                        pln->point.z);
}

double plane_hits(
vec_t    *base,    /* ray base (the viewpoint) */
vec_t    *dir,     /* ray direction unit vector */
object_t *obj)     /* the plane object          */
{
	plane_t *plane;
	double distance;
	double ndotv;
	double ndotd;
	double parcheck;
	vec_t hit, scaledvec;

	plane = (plane_t *)obj->priv;

	plane->ndotq = vec_dot(&plane->normal, &plane->point);
	ndotv = vec_dot(&plane->normal, base);
	ndotd = vec_dot(&plane->normal, dir);

	distance = (plane->ndotq - ndotv)/(ndotd);

	if(distance < 0.0)
	{
		return(-1);
	}

	vec_scale(distance, dir, &scaledvec);
	vec_sum(base, &scaledvec, &hit);

	parcheck = vec_dot(&plane->normal, dir);

	if(hit.z <= 0.0 && parcheck != 0.0)
	{
		vec_copy(&hit, &obj->hitloc);
		vec_copy(&plane->normal, &obj->normal);

		return(distance);
	}
	else
	{
		return(-1);
	}
}
