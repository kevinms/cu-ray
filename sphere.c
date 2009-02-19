/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * February 9, 2009
 * Program 3
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
