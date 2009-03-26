/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 25, 2009
 * Program 6
 *
 * Description
 * This program parses and loads the data for the sphere structure. 
 * Also a dumper function.
 ***********************************************************************/
 
#include "ray.h"


#define NUM_ATTRS (sizeof(sphere_parse) / sizeof(pparm_t))


void sphere_t::dumper(
FILE *out)
{

   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n",
                 "center", center.x, center.y,
                 center.z);
   fprintf(out, "%-12s %5.1lf \n",
                 "radius", radius);
}



double sphere_t::hits(
vec_t    *base,      /* ray base              */
vec_t    *dir)       /* unit direction vector */
{
	vec_t hit, sdir, hitdir;
	//sphere_t *sph;

	//sph = (sphere_t *)obj->priv;
	
	double a, b, c, t, d;
    vec_t vloc;
	
	vec_diff(&center, base, &vloc);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(&vloc, dir);
	c = vec_dot(&vloc, &vloc) - (radius * radius);

	d = b * b - 4 * a * c;

	if(d > 0.0)
	{
		t = (b * (-1.0) - sqrt(d)) / (2 * a);
	}
	else
	{
		return (-1);
	}

	vec_scale(t, dir, &sdir);
	vec_sum(base, &sdir, &hit);

	if(hit.z < 0.0)
	{
		vec_copy(&hit, &hitloc);
		vec_diff(&center, &hit, &hitdir);
		vec_unit(&hitdir, &hitnorm);
		return(t);
	}
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



static pparm_t sphere_parse[] =
{
   {"center",   3, 8, "%lf", 0},
   {"radius",  1, 8, "%lf", 0}
};




sphere_t::sphere_t(
FILE    *in,
model_t *model,
int      attrmax) : object_t(in, model)
{
   int  mask;

   strcpy(objtype, "sphere");

/* The parser is fairly generic but the address of where to */
/* put the data must be updated for each new object         */

   sphere_parse[0].loc = &center;
   sphere_parse[1].loc = &radius;
   mask = parser(in, sphere_parse, NUM_ATTRS, attrmax);
   assert(mask == 3);

//   vec_unit(radius, radius);
//   vec_copy(radius, hitnorm);
}


