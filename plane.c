#include "ray.h"

static char *pln_attrs[] = { "normal", "point" };
#define NUM_ATTRS (sizeof(pln_attrs) / sizeof(char *))

static inline void pln_load_point(FILE *in, plane_t *pln)
{
   int count;
   count = fscanf(in, "%lf %lf %lf", &pln->point.z, 
					&pln->point.y, &pln->point.z);
/* ensure that the required number of values were found */
   assert(count == 3);
}

static inline void pln_load_normal(FILE *in, plane_t *pln)
{
   int count;
   count = fscanf(in, "%lf %lf %lf", &pln->normal.z, 
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
		fscanf(in, "%s", attrname);
	}
	assert(attrname[0] == '}');

	obj->priv = (void *)pln;
	sprintf(obj->objtype, "plane");
	obj->dumper = plane_dump;
	
	return obj;
}

void plane_dump(
FILE *out,
object_t *obj)
{
	plane_t *pln;
	pln = (plane_t *)obj->priv;
        fprintf(stderr, "normal %10.1lf %5.1lf %5.1lf \n",
                        pln->normal.x, 
                        pln->normal.y, 
                        pln->normal.z);
						
        fprintf(stderr, "point %10.1lf %5.1lf %5.1lf \n",
                        pln->point.x, 
                        pln->point.y, 
                        pln->point.z);
}
