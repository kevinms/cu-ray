/* main.c */

#include "ray.h"

int main(
int argc,
char *argv[])
{
   model_t *model;
   material_t *mat;

/* Load and dump the model */

   model = model_init(stdin);
   assert(model != NULL);
   model_dump(stderr, model);

   mat = material_search(model, "orange");
   if (mat)
   {
      fprintf(stderr, "%d \n", mat->cookie);
      fprintf(stderr, "%4.1lf %4.1lf %4.1lf \n",
                        mat->ambient.r, mat->ambient.g, mat->ambient.b);
   }

   mat = material_search(model, "purple");
   assert(mat == NULL);

   return(0);
}

