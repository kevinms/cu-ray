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

/* Linked list management structures */
/* The ray tracer employs three separate lists           */
/*    objects   - visible objects                        */
/*    materials - that define the surface                */

typedef struct link_type
{
   struct link_type *next;    /* Next link in the list   */
   void             *item;    /* Item owned by this link */
}  link_t;

typedef struct list_type
{
   link_t  *head;             /* First link in the list */
   link_t  *tail;             /* Last link in the list  */
}  list_t;

typedef struct camera_type
{
   int    cookie;
   char   name[NAME_LEN];
   int    pixel_dim[2];    /* Projection screen size in pix */
   double world_dim[2];    /* Screen size in world coords   */
   vec_t  view_point;      /* Viewpt Loc in world coords    */
   irgb_t *pixmap;         /* Build image here              */
   int    attrmask;
}  cam_t;

typedef struct model_type
{
   cam_t   *cam;
   list_t  *mats;
   list_t  *objs;
   list_t  *lgts;
}  model_t;

typedef struct material_type
{
   int     cookie;
   char    name[NAME_LEN];
   drgb_t  ambient;         /* Reflectivity for materials  */
   drgb_t  diffuse;
   drgb_t  specular;
}  material_t;

typedef struct object_type
{
   int     cookie;
   char    objname[NAME_LEN];  /* left_wall, center_sphere */
   char    objtype[NAME_LEN];  /* plane, sphere, ...       */

   double  (*hits)(vec_t *base, vec_t *dir, struct object_type *);
                                 /* Hits function.             */
   void    (*dumper)(FILE*, struct object_type *);

/* Optional plugins for retrieval of reflectivity */
/* useful for the ever-popular tiled floor        */

   void    (*getamb) (struct object_type *, drgb_t *);
   void    (*getdiff)(struct object_type *, drgb_t *);
   void    (*getspec)(struct object_type *, drgb_t *);


/* Surface reflectivity data */

   material_t *mat;

   void    *priv;        /* Private type-dependent data */

   vec_t  hitloc;        /* Last hit point              */
   vec_t  normal;        /* Normal at hit point         */
} object_t;

/* An infinite plane */

typedef struct plane_type
{
   vec_t   normal;        /* Perpendicular to surfac */
   vec_t   point;         /* Any point on surface    */
   double  ndotq;         /* Computation optimizer   */
   void    *priv;         /* Data for specialized types  */
}  plane_t;

/* Tiled plane... descendant of plane */
typedef struct tplane_type
{
   char       matname[NAME_LEN];
   material_t *background;   /* background color */
   double     dimension[2]; /* dimension of tiles */
} tplane_t;

/* A sphere */
typedef struct sphere_type
{
   vec_t      center;     /* Location of the center */
   double     radius;     /* distance from center to surface */
}  sphere_t;

#include "rayfuns.h"
#include "rayhdrs.h"

