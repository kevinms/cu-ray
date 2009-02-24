
/* == main.c == */

/* == camera.c == */

void camera_getdir(
cam_t    *cam,
int      x,
int      y,
vec_t   *dir);

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

/* == list.c == */

/* malloc a new list header and initialize it */

list_t *list_init(
void);

/* Add an element to the end of a list */

void list_add(
list_t *list,
void   *entity);

/* == model.c == */

/* Init model data */

model_t *model_init(
FILE *in);

/* dump model data */

void model_dump(
FILE    *out,
model_t *model);

/* == material.c == */

/* Create a new material description */

void material_init(
FILE       *in,
model_t    *model,
int        attrmax);

/* Produce a formatted dump of the material list */

void material_dump(
FILE *out,
model_t *model);

/* Try to locate a material by name */

material_t *material_search(
model_t *model,
char    *name);

void material_getamb(
object_t *obj,
drgb_t   *dest);

void plane_dump(
FILE *out,
object_t *obj);

/* Determine if a vector projected from location *base  */
/* in direction *dir hits the plane.. If so the return */
/* value is the distance from the base to the point of  */
/* contact.                                             */

double  plane_hits(
vec_t    *base,      /* ray base              */
vec_t    *dir,       /* unit direction vector */
object_t *obj);

/* Create a new plane object and initialize it */

object_t *plane_init(
FILE *in,
model_t *model,
int  attrmax);

/* Create a new object description */

object_t   *object_init(
FILE       *in,
model_t    *model);

void object_dump(
FILE *out,
model_t *model);


void sphere_dump(
FILE *out,
object_t *obj);

/* Create a new sphere object and initialize it */

object_t *sphere_init(
FILE *in,
model_t *model,
int  attrmax);

/* Determine if a vector projected from location *base  */
/* in direction *dir hits the sphere.. If so the return */
/* value is the distance from the base to the point of  */
/* contact.                                             */

double  sphere_hits(
vec_t      *base,
vec_t      *dir,      /* MUST be unit vector */
object_t   *obj);

object_t *tplane_init(
FILE     *in,
model_t *model);

void tplane_amb(
object_t *obj,
drgb_t *value);

int tplane_foreground(
object_t *obj);

void tplane_dump(
FILE          *out,
object_t *obj);

object_t *find_closest_object(
list_t   *list,        /* Model structure               */
vec_t    *base,        /* Base of ray (viewpoint)       */
vec_t    *dir,         /* unit direction of ray         */
object_t *last_hit,    /* object last hit (ignore)      */
double   *retdist);    /* return dist to hit point here */

/**/
/* This function traces a single ray and returns the  */
/* composite intensity of the light it encounters     */
void ray_trace(
model_t *model,
vec_t    *base,        /* location of viewer or previous hit */
vec_t    *dir,         /* unit vector in direction of object */
drgb_t   *dpix,        /* pixel     return location */
double   total_dist,   /* distance ray has traveled so far */
object_t *last_hit);   /* most recently hit object */

void image_create(model_t *model);

void camera_write_image(
cam_t *cam);
