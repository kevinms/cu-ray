/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * February 24, 2009
 * Program 4
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
   //cam_t   *cam;
   model_t *model;
/* Load and dump the model */
   model = model_init(stdin);
   model_dump(stderr, model);
/* Raytrace the image */
   image_create(model);
   return(0);
}

