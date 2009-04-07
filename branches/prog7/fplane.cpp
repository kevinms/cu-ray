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
	plane_t::dumper(out); //call the regular plane dumper to
	                      //dump the regular stuff
	
    fprintf(out, "%-12s %5.1lf %5.1lf\n", "dims",
                 dims[0], dims[1]);
	fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "xdir",
                 xdir.x, xdir.y, xdir.z);
    fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "projxdir",
                 projxdir.x, projxdir.y, projxdir.z);
    fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "rot.row[0]",
                 rot.row[0].x, rot.row[0].y, rot.row[0].z);
    fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "rot.row[1]",
                 rot.row[1].x, rot.row[1].y, rot.row[1].z);
    fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "rot.row[2]",
                 rot.row[2].x, rot.row[2].y, rot.row[2].z);
}

double fplane_t::hits(
vec_t    *base,      /* ray base              */
vec_t    *dir)       /* unit direction vector */
{
	vec_t newloct;
	double t;

	t = plane_t::hits(base, dir);

	if(t == -1)
		return(-1);

	vec_diff(&point, &hitloc, &newloct);
	vec_xform(&rot, &newloct, &newloct);

	//fprintf(stderr, "%lf %lf\n", newloct.x, newloct.y);

	if(0 <= newloct.x && newloct.x <= dims[0])
	{
		if(0 <= newloct.y && newloct.y <= dims[1])
		{
			vec_copy(&newloct, &newloc);
			return(t);
		}
	}

	return(-1);
}

static pparm_t fplane_parse[] =
{
   {"xdir",    3, 8, "%lf", 0},
   {"dimensions", 2, 8, "%lf", 0}
};

fplane_t::fplane_t(FILE *in, model_t *model, 
int attrmax) : plane_t(in, model, 2)
{
	int mask;
	
	strcpy(objtype, "fplane");
	
	fplane_parse[0].loc = &xdir;
	fplane_parse[1].loc = &dims;
	mask = parser(in, fplane_parse, NUM_ATTRS, attrmax);
	assert(mask == 3);
	
	vec_project(&normal, &xdir, &projxdir);
	
	assert(projxdir.x == projxdir.y == projxdir.z != 0.0);
	
	vec_unit(&projxdir, &projxdir);
	
	vec_copy (&projxdir, &rot.row[0]);
	vec_copy (&normal, &rot.row[2]);
	
	vec_mult(&rot.row[0], &rot.row[2], &rot.row[1]);
}
