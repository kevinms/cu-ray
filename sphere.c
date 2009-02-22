/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * February 24, 2009
 * Program 4
 *
 * Description
 * This program alocates memory for a sphere structure and parses and
 * loads the data for the structure.  Also a sphere_dump() function.
 ***********************************************************************/

#include "ray.h"

static char *sph_attrs[] = { "center", "radius" };
#define NUM_ATTRS (sizeof(sph_attrs) / sizeof(char *))

static inline void sph_load_center(FILE *in, sphere_t *sph)
{
   int count;
   count = fscanf(in, "%lf %lf %lf", &sph->center.x, 
					&sph->center.y, &sph->center.z);
/* ensure that the required number of values were found */
   assert(count == 3);
}

static inline void sph_load_radius(FILE *in, sphere_t *sph)
{
   int count;
   count = fscanf(in, "%lf", &sph->radius);
/* ensure that the required number of values were found */
   assert(count == 1);
}

static int sphere_attr_load(
FILE      *in,
sphere_t *sph,       /* material to be filled in */
char      *attrname)
{
	int ndx;

	ndx = table_lookup(sph_attrs, NUM_ATTRS, attrname);
	assert(ndx >= 0);
	switch(ndx)
	{
		case 0:
			sph_load_center(in, sph); return 0;
		case 1:
			sph_load_radius(in, sph); return 0;
		default:
			return -1;
	}
}

object_t *sphere_init(
FILE *in,
model_t *model,
int attrmax)
{
	sphere_t *sph;
	object_t *obj;
	char attrname[NAME_LEN];
	int count;

	obj = object_init(in, model);
	sph = (sphere_t *)malloc(sizeof(sphere_t));
	assert(sph != NULL);
	memset(sph, 0, sizeof(sph));

	count = fscanf(in, "%s", attrname);
	assert(count == 1 && attrname[0] != '}');

	while( (count == 1) && (attrname[0] != '}') )
	{
		assert(sphere_attr_load(in, sph, attrname) == 0);
		*attrname = 0;
		fscanf(in, "%s", attrname);
	}
	assert(attrname[0] == '}');

	obj->priv = (void *)sph;
	sprintf(obj->objtype, "sphere");
	obj->dumper = sphere_dump;
	obj->hits = sphere_hits;

	return obj;
}

void sphere_dump(
FILE *out,
object_t *obj)
{
	sphere_t *sph;
	sph = (sphere_t *)obj->priv;

        fprintf(stderr, "center  %10.1lf %5.1lf %5.1lf \n",
                        sph->center.x, 
                        sph->center.y, 
                        sph->center.z);
        fprintf(stderr, "radius  %10.1lf \n\n",
                        sph->radius); 
}

double hits_sphere(
vec_t    *base,     /* ray base (the viewpoint) */
vec_t    *dir,      /* ray direction unit vector */
object_t *obj)      /* the sphere object          */
{
	double a, b, c, t, d;
	vec_t vloc;
	sphere_t *sph;

	sph = (sphere_t *)obj->priv;

	vec_diff(&sph->center, base, &vloc);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(&vloc, dir);
	c = vec_dot(&vloc, &vloc) - (sph->radius * sph->radius);

	d = b * b - 4 * a * c;
	if(d > 0.0)
	{
		t = (b * (-1.0) - sqrt(d)) / (2 * a);
		return(t);
	}
	else
	{
		return(-1);
	}
}

double sphere_hits(
vec_t    *base,     /* ray base (the viewpoint) */
vec_t    *dir,      /* ray direction unit vector */
object_t *obj)      /* the sphere object          */
{
	double t;
	vec_t hit, sdir, hitdir;
	sphere_t *sph;

	sph = (sphere_t *)obj->priv;

	t = hits_sphere(base, dir, obj);
	if(t == -1)
	{
		return(-1);
	}

	vec_scale(t, dir, &sdir);
	vec_sum(base, &sdir, &hit);

	if(hit.z < 0.0)
	{
		vec_copy(&hit, &obj->hitloc);
		vec_diff(&sph->center, &hit, &hitdir);
		vec_unit(&hitdir, &obj->normal);
		return(t);
	}
	else
	{
		return(-1);
	}
}
