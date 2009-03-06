/* image.c */

#include "ray.h"

static inline void make_pixel(
model_t *model,
int      x,
int      y)
{
   vec_t  raydir;
   vec_t  viewpt;
   drgb_t pix = {0.0, 0.0, 0.0};
   camera_t  *cam = model->cam;
   int    i;

   cam->camera_getviewpt(&viewpt);

   for (i = 0; i < AA_SAMPLES; i++)
   {
      cam->camera_getdir(x, y, &raydir);

/* call ray_trace to get the pixels intensity */

#ifdef DBG_PIX
      fprintf(stderr, "\nPIX %4d %4d - ", x, y);
#endif
      ray_trace(model, &viewpt, &raydir, &pix, 0.0, NULL);
   }

   cam->camera_setpix(x, y, &pix);
   return;
}

static inline void make_row(
model_t *model,
int      y)
{
   int   x;
   int   xdim;
   camera_t *cam = model->cam;

   xdim = cam->camera_getxdim();
   for (x = 0; x < xdim; x++)
   {
      make_pixel(model, x, y);
   }
}

/**/
/* This function is the driver for the raytracing procedure */

void image_create(
model_t  *model)
{
   int      y;
   int      ydim;

   camera_t   *cam = model->cam;

   ydim = cam->camera_getydim();

/* Fire ray(s) through each pixel in the window */

   for (y = 0; y < ydim;  y++)
   {
      make_row(model, y);
   }

/* Create ppm image */

   cam->camera_write_image(stdout);

}
