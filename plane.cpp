/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 25, 2009
 * Program 6
 *
 * Description
 * This program parses and loads the data for the plane structure. 
 * Also a dumper function.
 ***********************************************************************/
 
/* plane.c */

#include "ray.h"


#define NUM_ATTRS (sizeof(plane_parse) / sizeof(pparm_t))

/***/
void plane_t::dumper(
FILE *out)
{

   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n",
                 "normal", normal.x, normal.y,
                 normal.z);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n",
                 "point", point.x, point.y,
                 point.z);
}

/***/
/* Determine if a vector projected from location *base  */
/* in direction *dir hits the plane.. If so the return */
/* value is the distance from the base to the point of  */
/* contact.                                             */

double plane_t::hits(
vec_t    *base,      /* ray base              */
vec_t    *dir)       /* unit direction vector */
{
   double   ndotd;
   double   t;
   double   ndotb;

   ndotq = vec_dot(&normal, &point);
   ndotd = vec_dot(dir, &normal);

/* ndotd = 0 -> ray is parallel to the plane */

   if (ndotd == 0)
       return(-1);

   ndotb = vec_dot(&normal, base);

   t = (ndotq - ndotb) / ndotd;

   if (t <= 0)
      return(-1);

   vec_scale(t, dir, &hitloc);
   vec_sum(&hitloc, base, &hitloc);

   if (hitloc.z > 0.001)
      return(-1);

   return(t);
}

/* Parser parameter array for plane attributes */

static pparm_t plane_parse[] =
{
   {"point",   3, 8, "%lf", 0},
   {"normal",  3, 8, "%lf", 0}
};

/***/
/* Create a new plane object and initialize it */

plane_t::plane_t(
FILE    *in,
model_t *model,
int      attrmax) : object_t(in, model)
{
   int  mask;

   strcpy(objtype, "plane");

/* The parser is fairly generic but the address of where to */
/* put the data must be updated for each new object         */

   plane_parse[0].loc = &point;
   plane_parse[1].loc = &normal;
   mask = parser(in, plane_parse, NUM_ATTRS, attrmax);
   assert(mask == 3);

   vec_unit(&normal, &normal);
   vec_copy(&normal, &hitnorm);
   ndotq = vec_dot(&point, &normal);
}


