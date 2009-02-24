/* main.c */
#include "ray.h"
int main(
int argc,
char *argv[])
{
   //cam_t   *cam;
   model_t *model;
/* Load and dump the model */
   model = model_init(stdin);
   model_dump(stderr, model);
/* Raytrace the image */
   image_create(model);
   return(0);
}

