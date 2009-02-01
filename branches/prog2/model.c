/* model.c */

#include "ray.h"

static char *entities[] =
{
    "camera",
    "material",
};

#define NUM_ITEMS (sizeof(entities) / sizeof(entities[0]))

static inline void model_item_load(
FILE    *in,
model_t *model,
char    *enttype)
{
   int ndx;

   ndx = table_lookup(entities, NUM_ITEMS, enttype);
   assert(ndx >= 0);

   if (ndx == 0)
   {
   // camera_init(in, model, 0);
   }
   else if (ndx == 1)
   {
      material_init(in, model, 0);
   }

   return;
}

/* Load model data */

static void model_load(
FILE    *in,
model_t *model)
{
   char enttype[16];
   int  count;

   memset(enttype, 0, sizeof(enttype));

/* Here enttype should be one of "material",    */
/* "light", "plane"                             */

   count = fscanf(in, "%s", enttype);
   while (count == 1)
   {
      model_item_load(in, model, enttype);
      count = fscanf(in, "%s", enttype);
   }
}

/**/
/* Init model data */

model_t *model_init(
FILE *in)
{
   model_t *model = malloc(sizeof(model_t));
   assert(model != NULL);

   model->mats = list_init();
   assert(model->mats != NULL);

   model->lgts = list_init();
   assert(model->lgts != NULL);

   model->objs = list_init();
   assert(model->objs != NULL);

   model_load(in, model);

   return(model);

}

/**/
/* dump model data */

void model_dump(
FILE    *out,
model_t *model)
{
// camera_dump(out, model->cam);
   material_dump(out, model);
// object_dump(out, model);
// light_dump(out, model);
}

