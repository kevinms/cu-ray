/* main.c */

#include "ray.h"

int main(
int argc,
char *argv[])
{
   cam_t   *cam;
   char    entity[16];
   model_t *model = (model_t *)malloc(sizeof(model_t));


/* Read the word "camera" */

   fscanf(stdin, "%s", entity);

/* Load and dump camera data */

   camera_init(stdin, model, 0);

   cam = model->cam;

   assert(cam != NULL);
   camera_dump(stderr, cam);

   int x, y;
   vec_t dir;
   char buf[20];
   while (fscanf(stdin, "%d %d", &x, &y) == 2)
   {
       camera_getdir(cam, x, y, &dir);
       sprintf(buf, "pix (%3d, %3d) - ", x, y);
       vec_prn(stderr, buf, &dir);
   }
   return(0);
}

