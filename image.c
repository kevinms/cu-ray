/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * February 24, 2009
 * Program 4
 *
 * Description
 * I think this program does something with images. It might
 * make a ppm image based off of parameters it is passed from
 * other functions or something like that.
 ***********************************************************************/

#include "ray.h"

static inline void make_pixel(
model_t *model,
int x,
int y)
{
   vec_t raydir;
   drgb_t d_pix = {0.0, 0.0, 0.0};
   cam_t *cam = model->cam;

   camera_getdir(cam, x, y, &raydir);

   //fprintf(stderr, "\nPIX %4d %4d - ", y, x);

   ray_trace(model, &cam->view_point,
            &raydir, &d_pix, 0.0, NULL);
		 
   camera_setpix(cam, x, y, &d_pix);
   return;
}

static inline void make_row(model_t *model, int y)
{
   int x;
   cam_t *cam = model->cam;
   for (x = 0; x < cam->pixel_dim[0]; x++)
   {
      make_pixel(model, x, y);
   }
}

void image_create(model_t *model)
{
   int y;
   cam_t *cam = model->cam;
   /* Fire ray(s) through each pixel in the window */
   for (y = 0; y < cam->pixel_dim[1]; y++)
   {
      make_row(model, y);
   }
   /* Create ppm image */
   camera_write_image(model->cam);
}
