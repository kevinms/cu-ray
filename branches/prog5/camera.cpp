/* camera.c */

/* This module manages loading and dumping of camera data      */
/* This data includes:                                         */

/*     image width and depth in pixels from the command line   */

/*     world coordinate space width and depth in arbitrary     */
/*     units from the standard input                           */

/*     the location of the viewpoint (x, y, z) in world coords */
/*     from the standard input                                 */

/* The screen upon which the raytraced image is camected       */
/* lies in the z = 0 plane.                                    */
/* The point (0, 0, 0) maps to the center of the camera        */
/* screen                                                      */

#include "ray.h"

static pparm_t camera_parse[] =
{
   {"pixeldim",  2, 4, "%d",  0},
   {"worlddim",  2, 8, "%lf", 0},
   {"viewpoint", 3, 8, "%lf", 0}
};

#define NUM_ATTRS (sizeof(camera_parse) / sizeof(pparm_t))

/**/
int camera_t::camera_getydim(
void)
{
   return(pixel_dim[1]);
}

/**/
void camera_t::camera_getviewpt(
vec_t *view)
{
   vec_copy(&view_point, view);
}

/**/
int camera_t::camera_getxdim(
void)
{
   return(pixel_dim[0]);
}


/**/
void camera_t::camera_getdir(
int      x,
int      y,
vec_t   *dir)
{
   vec_t world;
   double dx = x;
   double dy = y;

   world.x = 1.0 * dx / (pixel_dim[0] - 1) * world_dim[0];
   world.y = 1.0 * dy / (pixel_dim[1] - 1) * world_dim[1];
   world.z = 0.0;

   vec_diff(&view_point, &world, dir);
   vec_unit(dir, dir);
}

static inline void scale_and_clamp(
drgb_t *pix)
{
   int fact = 256;
   fact /= AA_SAMPLES;

   pix->r *= fact;
   pix->g *= fact;
   pix->b *= fact;

   if (pix->r > 255)
      pix->r = 255;

   if (pix->g > 255)
      pix->g = 255;

   if (pix->b > 255)
      pix->b = 255;
}

/**/
void camera_t::camera_setpix(
int      x,
int      y,
drgb_t   *pix)
{
   int     maprow;
   irgb_t *maploc;

   maprow = pixel_dim[1] - y - 1;
   maploc = pixmap + maprow * pixel_dim[0] + x;

   scale_and_clamp(pix);

   maploc->r = (unsigned char)pix->r;
   maploc->g = (unsigned char)pix->g;
   maploc->b = (unsigned char)pix->b;
}


/**/
/* Initialize viewpoint data */

camera_t::camera_t(
FILE *in)
{
   char  buf[256];
   int   mask;

   assert (fscanf(in, "%s", name) == 1);

   fscanf(in, "%s", buf);
   assert(buf[0] == '{');

   cookie = CAM_COOKIE;

   camera_parse[0].loc = &pixel_dim;
   camera_parse[1].loc = &world_dim;
   camera_parse[2].loc = &view_point;

   mask = parser(in, camera_parse, NUM_ATTRS, 0);
   assert(mask == 7);

/* Allocate a pixmap to hold the ppm image data */

   pixmap = (irgb_t *)malloc(sizeof(irgb_t) * pixel_dim[0] *
                                              pixel_dim[1]);

}

/**/
/* Dump the camera data */

void camera_t::camera_dump(
FILE   *out)
{

   fprintf(out, "%-12s %s\n", "camera", name);

   fprintf(out, "%-12s %5d %5d \n", "pixel_dim",
                  pixel_dim[0],  pixel_dim[1]);

   fprintf(out, "%-12s %5.1lf %5.1lf \n", "world_dim",
                  world_dim[0], world_dim[1]);

   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "view_point",
                  view_point.x, view_point.y,
                  view_point.z);

   fprintf(out, "\n");
}

/**/

void camera_t::camera_write_image(
FILE *out)
{
   fprintf(out, "P6 %d %d 255\n",
                  pixel_dim[0], pixel_dim[1]);

   fwrite(pixmap, 3, pixel_dim[0] *
                  pixel_dim[1], out);
}
