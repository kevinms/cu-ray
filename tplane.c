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

static char *tpln_attrs[] = { "dimension", "altmaterial" };
#define NUM_ATTRS (sizeof(tpln_attrs) / sizeof(char *))

static inline void tpln_load_dimension(FILE *in, tplane_t *tpln)
{
   int count;
   count = fscanf(in, "%lf %lf", &tpln->dimension[0], &tpln->dimension[1]);
/* ensure that the required number of values were found */
   assert(count == 2);
}

static inline void tpln_load_altmaterial(
 FILE *in, tplane_t *tpln, model_t *model)
{
   int count;
   count = fscanf(in, "%s", tpln->matname);
   tpln->background = material_search(model, tpln->matname);
/* ensure that the required number of values were found */
   assert(count == 1);
}

static int tplane_attr_load(
FILE      *in,
tplane_t *tpln,       /* material to be filled in */
char      *attrname,
model_t *model)
{
    int ndx;

    ndx = table_lookup(tpln_attrs, NUM_ATTRS, attrname);
    assert(ndx >= 0);
    switch(ndx)
    {
        case 0:
            tpln_load_dimension(in, tpln); return 0;
        case 1:
            tpln_load_altmaterial(in, tpln, model); return 0;
        default:
            return -1;
    }
}

object_t *tplane_init(
FILE     *in,
model_t *model)
{
    char attrname[NAME_LEN];
    int count;
	object_t *obj;
    tplane_t *tpln;
	plane_t *pln;

    tpln = (tplane_t *)malloc(sizeof(tplane_t));
    assert(tpln != NULL);
    memset(tpln, 0, sizeof(tpln));

	obj = plane_init(in, model, 2);
	pln = (plane_t *)obj->priv;
	pln->priv = (void *)tpln;

    count = fscanf(in, "%s", attrname);
    assert(count == 1 && attrname[0] != '}');

    while( (count == 1) && (attrname[0] != '}') )
    {
        assert(tplane_attr_load(in, tpln, attrname, model) == 0);
        *attrname = 0;
        fscanf(in, "%s", attrname);
    }
    assert(attrname[0] == '}');

    obj->getamb = tplane_amb;
    obj->dumper = tplane_dump;
    sprintf(obj->objtype, "tiled plane");
    
    return obj;
}

void tplane_amb(
object_t *obj,
drgb_t *value)
{
	plane_t *pln = (plane_t *)obj->priv;
	tplane_t *tpln = (tplane_t *)pln->priv;
	material_t *mat = tpln->background;
	

	int foreground = tplane_foreground(obj);
	if(foreground)
	{
		material_getamb(obj, value);
	}
	else
	{
		drgb_copy(&mat->ambient, value);
	}
}

int tplane_foreground(
object_t *obj)
{
	plane_t *pln = (plane_t *)obj->priv;
	tplane_t *tpln = (tplane_t *)pln->priv;

	double x_ndx = (obj->hitloc.x + 10000) / tpln->dimension[0];
	double z_ndx = (obj->hitloc.z + 10000) / tpln->dimension[1];

	if((int)(x_ndx + z_ndx) % 2 == 0)
	{
		return(1);
	}
	else
	{
		return(0);
	}
}

void tplane_dump(
FILE          *out,
object_t *obj)
{
	plane_dump(out, obj);
	plane_t *pln = (plane_t *)obj->priv;
	tplane_t *tpln = (tplane_t *)pln->priv;

	fprintf(stderr, "dimension %8.1lf %5.1lf \n", 
			tpln->dimension[0], tpln->dimension[1]);
	fprintf(stderr, "altmaterial       %s \n", 
			tpln->background->name);
}
