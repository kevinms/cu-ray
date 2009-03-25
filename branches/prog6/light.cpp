/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 25, 2009
 * Program 6
 *
 * Description
 * This program parses and loads the data for the light class. 
 * Also a dumper function.
 ***********************************************************************/
 
/* light.c */

#include "ray.h"
#define NUM_ATTRS (sizeof(light_parse) / sizeof(pparm_t))

/* Parser parameter array for light attributes */

static pparm_t light_parse[] =
{
   {"location",   3, 8, "%lf", 0},
   {"emissivity",  3, 8, "%lf", 0}
};


void light_t::dumper(FILE *out)
{

   assert(cookie == LGT_COOKIE);
   fprintf(out, "%-12s %s \n", "light", name);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "location", 
				location.x, location.y, location.z);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "emissivity", 
				emissivity.r, emissivity.g, emissivity.b);
}

void light_t::illuminate(
model_t     *model,
object_t    *hitobj, /* The object hit by the ray    */
drgb_t      *pixel)   /* add illumination here       */
{
   vec_t    dir;    // unit direction to light from hitpt
   vec_t    revdir; // unit direction from light to hitpt
   object_t *obj;   // closest object in dir to light
   double   close;  // dist to closest object in dir to light
   double   cos;    // of angle between normal and dir to light
   double   dist;   // to the light from hitpoint
   drgb_t   diffuse = {0.0, 0.0, 0.0};
/* Compute the distance from the hit to the light and a unit */
/* vector in the direction of the light from hitpt           */
	vec_diff(hitobj->hitloc, location, dir);  // what is this
	vec_unit(dir, dir);  // idk
   ..........
/* Test the object for self-occlusion and return if occluded */
   ..........
/* Ask find_closest_object() if a ray fired toward the light */
/* hits a "regular" object. Pass "hitobj" as the "lasthit"   */
/* parameter so it won't be hit again at distance 0.         */
   ..........
/* If an object is hit and the distance to the hit is   */
/* closer to the hitpoint than the light is, return     */
   ............
/* Arriving at this point means the light does illuminate */
/* object. Ask hitobj->getdiff() to return diffuse        */
/* reflectivity                                           */
   .............
/* Multiply componentwise the diffuse reflectivity by     */
/* the emissivity of the light.                           */
   .............
/* Scale the resulting diffuse reflectivy by cos/dist     */
   ..............
/* Add scaled value to *pixel.                            */
}


/***/
/* Create a new light object and initialize it */

light_t::light_t(FILE *in, model_t *model, int attrmax)
{
   int mask;
   list_t *list;

   fscanf(in, "%s", name);
//   cookie = LGT_COOKIE;

/* The parser is fairly generic but the address of where to */
/* put the data must be updated for each new object         */

   light_parse[0].loc = &location;
   light_parse[1].loc = &emissivity;
   mask = parser(in, light_parse, NUM_ATTRS, attrmax);
   assert(mask == 3);

   list = model->lgts;
   list->add((void *)this);
}


/**/
/* Produce a formatted dump of the light list */
void light_dump(
FILE *out,
model_t *model)
{
   list_t *list;
   light_t *light;
   list = model->lgts;
   light = (light_t *)list->start();

   while (light != NULL)
   {
      light->dumper(out);
      fprintf(out, "\n");
      light = (light_t *)list->get_next();
   }
}

