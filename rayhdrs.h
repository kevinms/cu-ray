/* == camera.c == */

/* Given pixel coordinates fill in unit vector */
/* from the viewpoint to the pixel.            */

void camera_getdir(
cam_t    *cam,
int      x,
int      y,
vec_t   *dir);

/* Convert pixel from drgb to irgb and store in pixmap */

void camera_setpix(
cam_t    *cam,
int      x,
int      y,
drgb_t   *pix);

/* Initialize viewpoint data */

void   camera_init(
FILE    *in,
model_t *model,
int     attrmax);   /* ignore this */

/* Dump the camera data */

void camera_dump(
FILE   *out,
cam_t *cam);

