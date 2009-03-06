/* main.c */

#include "ray.h"

int main(
int argc,
char *argv[])
{
   model_t *model;

/* Load and dump the model */

   model = new model_t(stdin);
   assert(model != NULL);
   model->dump(stderr);

#if 0
   vec_t   raydir;
   drgb_t  pix = {0, 0, 0};
   cam_getdir(cam, 307, 83, &raydir);
   ray_trace(model, &cam->view_point, &raydir, &pix, 0.0, NULL);
#endif

/* Raytrace the image */

   image_create(model);

   return(0);
}

