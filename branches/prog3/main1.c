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

   return(0);
}

