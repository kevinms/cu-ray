/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 25, 2009
 * Program 6
 *
 * Description
 * This program parses and loads the data for the fplane structure. 
 * Also a dumper function.
 ***********************************************************************/

/* fplane.cpp */

#include "ray.h"


#define NUM_ATTRS (sizeof(fplane_parse) / sizeof(pparm_t))

void fplane_t::dumper(FILE *out)
{
	
}

double fplane_t::hits(
vec_t    *base,      /* ray base              */
vec_t    *dir)       /* unit direction vector */
{
	vec_t newloc;
	double t;

	t = plane_t::hits(base, dir);

	if(t == -1)
		return(-1);

	vec_diff(point, hitloc, newloc);
	//vec_xform(rot, , );
	vec_xform(rot, newloc, newloc);

	if(0 <= newloc.x && newloc.x <= dims[0])
	{
		if(0 <= newloc.y && newloc.y <= dims[1])
			return(-1);
	}
}

static pparm_t fplane_parse[] =
{
   {"point",   3, 8, "%lf", 0},
   {"normal",  3, 8, "%lf", 0}
};

fplane_t::fplane_t(FILE *in, model_t *model, 
int attrmax) : plane_t(in, model, 2)
{
	
}
