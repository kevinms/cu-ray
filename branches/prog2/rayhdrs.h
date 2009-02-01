
/* == main.c == */

/* == camera.c == */

void cam_getdir(
cam_t    *cam,
int      x,
int      y,
vec_t   *dir);

void cam_setpix(
cam_t    *cam,
int      x,
int      y,
drgb_t   *pix);

/* Initialize viewpoint data */

cam_t *cam_init(
FILE *in);

/* Dump the camera data */

void cam_dump(
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

/* Search the material list looking for a material */
/* having the specified color name                 */


material_t *material_search(
model_t *model,
char    *name);

