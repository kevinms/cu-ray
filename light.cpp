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
 
/* plane.c */

#include "ray.h"
#define NUM_ATTRS (sizeof(light_parse) / sizeof(pparm_t))

/* Parser parameter array for light attributes */

static pparm_t light_parse[] =
{
   {"location",   3, 8, "%lf", 0},
   {"emissivity",  3, 8, "%lf", 0}
};

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

void light_t::dumper(FILE *out)
{

   assert(cookie == LGT_COOKIE);
   fprintf(out, "%-12s %s \n", "light", name);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "location", 
				location.x, location.y, location.z);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "emissivity", 
				emissivity.r, emissivity.g, emissivity.b);
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

