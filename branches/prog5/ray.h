/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 9, 2009
 * Program 5
 *
 * Description
 * Structure definitions
 ***********************************************************************/
 
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
#include "list.h"

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


class camera_t
{
public:
//        camera_t();
          camera_t(FILE *in);
   void   camera_getdir(int x, int y, vec_t *dir);
   void   camera_setpix(int x,int y, drgb_t *pix);
   int    camera_getxdim(void);
   int    camera_getydim(void);
   void   camera_getviewpt(vec_t *view);
   void   camera_dump(FILE *out);
   void   camera_write_image(FILE *out);

private:
   int    cookie;
   char   name[NAME_LEN];
   int    pixel_dim[2];    /* Projection screen size in pix */
   double world_dim[2];    /* Screen size in world coords   */
   vec_t  view_point;      /* Viewpt Loc in world coords    */
   irgb_t *pixmap;         /* Build image here              */
};

class model_t
{
public:
           model_t(FILE *);
   void    dump(FILE *);
   camera_t   *cam;
   list_t  *mats;
   list_t  *objs;
   list_t  *lgts;

private:
   void model_item_load(FILE *,char    *);
   void model_load(FILE *);

};

typedef struct pparm_type
{
   char *attrname;          /* Attribute name                   */
   int  numvals;            /* Number of attribute values       */
   int  valsize;            /* Size of one attrib value (bytes) */
   char *fmtstr;            /* Format string to scan with       */
   void *loc;               /* Where to store first attribute   */
}  pparm_t;

class material_t
{
public:
   material_t(){};
   material_t(FILE *in, model_t *model, int attrmax);
   void  material_getamb(drgb_t *dest);
   void  material_getdiff(drgb_t *dest);
   void  material_getspec(drgb_t *dest);
   char *material_getname();
   inline void material_item_dump(FILE *out);

private:
   int     cookie;
   char    name[NAME_LEN];
   drgb_t  ambient;         /* Reflectivity for materials  */
   drgb_t  diffuse;
   drgb_t  specular;
};

class object_t
{
public:

   object_t(){};
   object_t(FILE *in, model_t *model);
   virtual ~object_t(){};

   virtual  double  hits(vec_t *base, vec_t *dir){return(-1.0);};
   virtual  void    dumper(FILE*){};

/* Virtual  plugins for retrieval of reflectivity */

   virtual    void    getamb(drgb_t *);
   virtual    void    getdiff(drgb_t *);
   virtual    void    getspec(drgb_t *);

   inline     void    object_item_dump(FILE *out);

protected:

   int     cookie;
   char    objtype[NAME_LEN];  /* plane, sphere, ...       */

   vec_t   hitloc;             /* Last hit point              */
   vec_t   hitnorm;            /* Normal at hit point         */

/* Surface reflectivity data */

   material_t *mat;

private:
   char   objname[NAME_LEN];  /* left_wall, center_sphere */

};

class plane_t: public object_t
{
public:
   plane_t();
   plane_t(FILE *, model_t *, int);

   virtual double  hits(vec_t *base, vec_t *dir);
   virtual void    dumper(FILE *);
#if 0
   virtual void    getamb(double *w) {matamb(w);};
   virtual void    getdiff(double *w){matdiff(w);};
   virtual void    getspec(double *w){matspec(w);};
#endif

protected:
   vec_t   normal;
   vec_t   point;

private:
   double  ndotq;
};


/* Tile plane... descendant of plane */

typedef struct tplane_type
{
   char       matname[NAME_LEN];
   material_t *mat;          /* background color    */
   vec_t      direction;     /* direction of tiling */
   double     dimension[2];  /* dimension of tiles  */
   vec_t      udir;          /* unit direction vec  */
   mat_t      rot;           /* rotation matrix     */
   mat_t      irot;          /* inverse rotation    */
}  tplane_t;

class sphere_t: public object_t
{
public:
   sphere_t();
   sphere_t(FILE *, model_t *, int);

   virtual double  hits(vec_t *base, vec_t *dir);
   virtual void    dumper(FILE *);
// virtual void    getamb(drgb_t *);

protected:
   vec_t   center;
   double  radius;
   vec_t   scale;
private:


};


#include "rayfuns.h"
#include "rayhdrs.h"

