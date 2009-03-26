/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 25, 2009
 * Program 6
 *
 * Description
 * This program parses and loads the data for the object structure.
 * Also a dumper function.
 ***********************************************************************/
 
/* object.c */

#include "ray.h"


/***/
/* Create a new object description */

object_t::object_t(
FILE       *in,
model_t    *model)
{
   char attrname[NAME_LEN];
   char matname[NAME_LEN];
   list_t *list = model->objs;

   int count;

/* Read the descriptive name of the object */
/* left_wall, center_sphere, etc.          */

   count = fscanf(in, "%s", objname);
   assert(count == 1);

/* Consume the delimiter */

   attrname[0] = 0;
   count = fscanf(in, "%s", attrname);
   assert(attrname[0] == '{');

   cookie = OBJ_COOKIE;

/* First attribute must be material */

   count = fscanf(in, "%s", attrname);
   assert(count == 1);
   count = strcmp(attrname, "material");
   assert(count == 0);
   count = fscanf(in, "%s", matname);
   assert(count == 1);

   mat = material_search(model->mats, matname);
   assert(mat != NULL);

/* Add the object to the list */

   list->add((void *)this);
}

/* The default color "getters" just invoke the */
/* corresponding material getters              */

void object_t::getamb(drgb_t *amb)
{
   material_t *mat;

   mat = this->mat;
   mat->material_getamb(amb);
}

void object_t::getdiff(drgb_t *diff)
{
   material_t *mat;

   mat = this->mat;
   mat->material_getdiff(diff);
}

void object_t::getspec(drgb_t *spec)
{
   material_t *mat;

   mat = this->mat;
   mat->material_getspec(spec);
}

/* This function should be a class method because */
/* (1) it touches only one object structure and   */
/* (2) it needs access to the private variables   */


inline void object_t::object_item_dump(
FILE     *out)
{

   assert(cookie == OBJ_COOKIE);
   fprintf(out, "%-12s %s \n", objtype, objname);
   fprintf(out, "%-12s %s \n", "material",
                     this->mat->material_getname());
   this->dumper(out);
}

/**/
/* This function can't be a class method because */
/* (1) it must process EVERY object and          */
/* (2) it doesn't need to access private data    */
/*     of ANY object                             */

void object_dump(
FILE *out,
list_t *list)
{
   object_t *obj = (object_t *)list->start();

   while (obj != NULL)
   {
      obj->object_item_dump(out);
      fprintf(out, "\n");
      obj = (object_t *)list->get_next();
   }
}

