/* ray.h */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <memory.h>
#include <assert.h>

#define NAME_LEN   16        /* max length of entity names */

#define OBJ_COOKIE 12345678
#define MAT_COOKIE 32456123
#define LGT_COOKIE 30492344
#define CAM_COOKIE 49495923

#define MAX_DIST   32

#define CAM_MASK 7

#include "vector.h"

/* Two pixel value structures are used                   */
/* Computations are done in the double precision domain  */
/* where 0.0 means black and 1.0 means maximum intensity */
/* The raytracing algorithm can DEFINITELY produce       */
/* pixel values that exceed 1.0 scale and then clamp     */
/* them before assigning them to irgb_types              */

typedef struct drgb_type
{
   double r;
   double g;
   double b;
}  drgb_t;

/* The .ppm file requires the usual r-g-b values in the  */
/* range 0-255.  This structure maps one of them.        */

typedef struct irgb_type
{
   unsigned char r;
   unsigned char g;
   unsigned char b;
}  irgb_t;

typedef struct camera_type
{
   int    cookie;
   int    attrmask;
   char   name[NAME_LEN];
   int    pixel_dim[2];    /* Projection screen size in pix */
   double world_dim[2];    /* Screen size in world coords   */
   vec_t  view_point;      /* Viewpt Loc in world coords    */
   irgb_t *pixmap;         /* Build image here              */
}  cam_t;

typedef struct model_type
{
   cam_t   *cam;
// list_t  *mats;
// list_t  *objs;
// list_t  *lgts;
}  model_t;

/* Have to come LAST because they reference the structure */
/* types that are described above                         */

#include "rayfuns.h"
#include "rayhdrs.h"

