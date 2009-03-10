/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 9, 2009
 * Program 5
 *
 * Description
 * This is the main program that takes the command line arguments and 
 * outputs an image to the requested ppm file.
 ***********************************************************************/
 
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

