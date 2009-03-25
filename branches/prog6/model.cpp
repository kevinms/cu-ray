/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 9, 2009
 * Program 5
 *
 * Description
 * This program parses and loads the data for the model structure.
 * Also a dumper function.
 ***********************************************************************/
 
/* model.c */

#include "ray.h"

static char *items[] =
{
    "camera",
    "material",
    "plane",
	"sphere",
#if 0
    "pplane",
    "light",
    "tiled_plane",
    "ellipsoid",
#endif
};

#define NUM_ITEMS (sizeof(items) / sizeof(char *))

 void model_t::model_item_load(
FILE    *in,
char    *itemtype)
{
   int ndx;

   ndx = table_lookup(items, NUM_ITEMS, itemtype);

   assert(ndx >= 0);

   switch (ndx)
   {
   case 0:
      cam = new camera_t(in);
      break;
   case 1:
      new material_t(in, this, 0);
      break;
   case 2:
      new plane_t(in, this, 0);
      break;
   case 3:
      new sphere_t(in, this, 0);
      break;
#if 0
   case 4:
      new light_t(in, this, 0);
      break;
#endif
   }
   return;
}

/* Load model data */

 void model_t::model_load(
FILE    *in)
{
   char itemtype[16];
   int  count;

   memset(itemtype, 0, sizeof(itemtype));

/* Here itemtype should be one of "material",    */
/* "light", "plane"                             */

   count = fscanf(in, "%s", itemtype);
   while (count == 1)
   {
      model_item_load(in, itemtype);
      count = fscanf(in, "%s", itemtype);
   }
}

/***/
/* Init model data */

model_t::model_t(
FILE *in)
{

   mats = new list_t;
   assert(mats != NULL);

   lgts = new list_t;
   assert(lgts != NULL);

   objs = new list_t;
   assert(objs != NULL);

   model_load(in);

}

/***/
/* dump model data */

void model_t::dump(
FILE          *out)
{
   cam->camera_dump(out);
   material_dump(out, mats);
   object_dump(out, objs);
   light_dump(out, this);
}

