/* camera.c */

/* This module contains the functions that involve the camera */

#include "ray.h"

static char *cam_attrs[] = { "pixeldim", "worlddim", "viewpoint" };
#define NUM_ATTRS (sizeof(cam_attrs)/sizeof(char *))

static inline void cam_load_pixeldim(FILE *in, cam_t *cam)
{
   int count;
   assert(cam->cookie == CAM_COOKIE);
   count = fscanf(in, "%d %d",
                  &cam->pixel_dim[0], &cam->pixel_dim[1]);
/* ensure that the required number of values were found */
   assert(count == 2);
}

static inline void cam_load_worlddim(FILE *in, cam_t *cam)
{
   int count;
   assert(cam->cookie == CAM_COOKIE);
   count = fscanf(in, "%lf %lf",
                  &cam->world_dim[0], &cam->world_dim[1]);

/* ensure that the required number of values were found */
   assert(count == 2);
}

static inline void cam_load_viewpoint(FILE *in, cam_t *cam)
{
   int count;
   assert(cam->cookie == CAM_COOKIE);
   count = fscanf(in, "%lf %lf %lf",
                  &cam->view_point.x, &cam->view_point.y,
                  &cam->view_point.z);
/* ensure that the required number of values were found */
   assert(count == 3);
}

static inline void cam_attr_load(FILE *in, cam_t *cam, char *attr)
{
   int ndx;

/* verify structure pointer */
   assert(cam->cookie == CAM_COOKIE);

/* Perform table lookup and ensure it worked */
   ndx = table_lookup(cam_attrs, NUM_ATTRS, attr);
   assert(ndx >= 0);

/* Remember which attribute was found */
   //cam->attrmask |= 1 << ndx;
   if (ndx == 0)
      cam_load_pixeldim(in, cam);
   else if (ndx == 1)
      cam_load_worlddim(in, cam);
   else
      cam_load_viewpoint(in, cam);
}

/**/
/* Initialize camera data */

void camera_init(FILE *in, model_t *model, int attrmax)
{
   char  buf[256];
   int count;

   cam_t *cam  = (cam_t *)malloc(sizeof(cam_t));
   assert(cam != NULL);
   memset(cam, 0, sizeof(cam));
   cam->cookie = CAM_COOKIE;

   assert(fscanf(in, "%s", cam->name) == 1);

   fscanf(in, "%s", buf);
   assert(buf[0] == '{');

   count = fscanf(in, "%s", buf);
   while( (count == 1) && (buf[0] != '}') )
      {
         cam_attr_load(in, cam, buf);
         *buf = 0;
         fscanf(in, "%s", buf);
      }

   assert(buf[0] == '}');
   //assert(cam->attrmask == CAM_MASK);

   cam->pixmap = malloc(cam->pixel_dim[0] * 
		cam->pixel_dim[1] * sizeof(irgb_t));

   model->cam = cam;
}

/**/
/* Dump the camera data */

void camera_dump(
FILE   *out,
cam_t *cam)
{
   assert(cam->cookie == CAM_COOKIE);

   fprintf(out, "%-12s %s\n", "camera", cam->name);

   fprintf(out, "%-12s %5d %5d\n", "pixel_dim", 
		cam->pixel_dim[0], cam->pixel_dim[1]);

   fprintf(out, "%-12s %5.1lf %5.1lf\n", "world_dim", 
		cam->world_dim[0], cam->world_dim[1]);

   fprintf(out, "%-12s %5.1lf %5.1lf %5.1lf\n", "view_point", 
		cam->view_point.x, cam->view_point.y, cam->view_point.z);
}

/**/
/* Compute the direction of a ray fired through pixel */
/* coordinates (x, y)                                 */

void camera_getdir(
cam_t    *cam,
int      x,
int      y,
vec_t   *dir)
{

   assert(cam->cookie == CAM_COOKIE);

   double world_x = cam->world_dim[0] * x / (cam->pixel_dim[0] - 1);
   double world_y = cam->world_dim[1] * y / (cam->pixel_dim[1] - 1);

   vec_t pix = {world_x, world_y, 0.0};

   vec_diff(&cam->view_point, &pix, dir);

   vec_unit(dir, dir);
}
