/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 25, 2009
 * Program 6
 *
 * Description
 * This program parses and loads the data for the material structure.
 * Also a dumpter function.
 ***********************************************************************/
 
/* material.c */

#include "ray.h"

static pparm_t mat_parse[] =
{
   {"ambient",   3, 8, "%lf", 0},
   {"diffuse",   3, 8, "%lf", 0},
   {"specular",  3, 8, "%lf", 0}
};

#define NUM_ATTRS (sizeof(mat_parse) / sizeof(pparm_t))

/***/
/* Create a new material description */

material_t::material_t(
FILE       *in,
model_t    *model,
int        attrmax)
{
   char attrname[NAME_LEN];
   list_t *list = model->mats;
   int count;
   int mask;

/* Create a new material structure and initialize it */

   cookie = MAT_COOKIE;

/* Read the descriptive name of the material */
/* (dark_red, light_blue, etc.               */

   count = fscanf(in, "%s", name);
   assert(count == 1);

   count = fscanf(in, "%s", attrname);
   assert(*attrname == '{');

   mat_parse[0].loc = &ambient;
   mat_parse[1].loc = &diffuse;
   mat_parse[2].loc = &specular;
   mask = parser(in, mat_parse, NUM_ATTRS, 0);

   assert(mask != 0);

   list->add((void *)this);
}

char * material_t::material_getname()
{
   return(name);
};

inline void material_t::material_item_dump(
FILE       *out)
{
   fprintf(out, "%-12s %s \n", "material", name);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "ambient",
                 ambient.r, ambient.g, ambient.b);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n", "diffuse",
                 diffuse.r, diffuse.g, diffuse.b);
   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf \n\n", "specular",
                 specular.r, specular.g, specular.b);

}

/**/
/* Produce a formatted dump of the material list */

void material_dump(
FILE *out,
list_t *list)
{
   material_t *mat = (material_t *)list->start();

   while (mat != NULL)
   {
      mat->material_item_dump(out);
      mat = (material_t *)list->get_next();
   }
}


/**/
/* Try to locate a material by name */

material_t *material_search(
list_t  *list,
char    *name)
{
   material_t *mat = (material_t *)list->start();

   while (mat != NULL)
   {

      if (strcmp(name, mat->material_getname()) == 0)
         return(mat);
      mat = (material_t *)list->get_next();
   }

   return(NULL);
}



/* */
void material_t::material_getamb(
drgb_t   *dest)
{

   assert(cookie == MAT_COOKIE);

   dest->r = ambient.r;
   dest->g = ambient.g;
   dest->b = ambient.b;

}

/* */
void material_t::material_getdiff(
drgb_t   *dest)
{

   assert(cookie == MAT_COOKIE);

   dest->r = diffuse.r;
   dest->g = diffuse.g;
   dest->b = diffuse.b;

}

/* */
void material_t::material_getspec(
drgb_t   *dest)
{

   assert(cookie == MAT_COOKIE);

   dest->r = specular.r;
   dest->g = specular.g;
   dest->b = specular.b;

}


