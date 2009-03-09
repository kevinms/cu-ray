#include "ray.h"


#define NUM_ATTRS (sizeof(plane_parse) / sizeof(pparm_t))


void sphere_t::dumper(
FILE *out)
{

   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n",
                 "center", center.x, center.y,
                 center.z);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n",
                 "radius", &radius);
}



double sphere_t::hits(
vec_t    *base,      /* ray base              */
vec_t    *dir)       /* unit direction vector */
{
	double a, b, c, t, d;

	vec_diff(&center, base, &vec_t);
	a = vec_dot(dir, dir);
	b = 2.0 * vec_dot(&vec_t, dir);
	c = vec_dot(&vec_t, &vec_t) - (&radius * &radius);

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



static sphere_t sphere_parse[] =
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

   strcpy(objtype, "plane");

/* The parser is fairly generic but the address of where to */
/* put the data must be updated for each new object         */

   sphere_parse[0].loc = &center;
   sphere_parse[1].loc = &radius;
   mask = parser(in, sphere_parse, NUM_ATTRS, attrmax);
   assert(mask == 3);

   vec_unit(&radius, &radius);
   vec_copy(&radius, &hitnorm);
   ndotq = vec_dot(&center, &radius);
}


