
/* == main.c == */

/* == list.c == */



/* == image.c == */

/* This function is the driver for the raytracing procedure */

void image_create(
model_t  *model);

/* == model.cpp == */

/* == material.cpp == */

/* Produce a formatted dump of the material list */

void material_dump(
FILE *out,
list_t *list);

/* Try to locate a material by name */

material_t *material_search(
list_t *list,
char   *name);

/* == raytrace.c == */

/* This function traces a single ray and returns the composite */
/* intensity of the light it encounters                        */

void ray_trace(
model_t  *model,
vec_t    *base,        /* location of viewer or previous hit */
vec_t    *dir,         /* unit vector in direction of object */
drgb_t   *pix,         /* pixel     return location          */
double   total_dist,   /* distance ray has traveled so far   */
object_t *last_hit);

/* == plane.cpp == */

/* == object.cpp == */

/* Find the closest object intersection on the ray based */
/* at "base" and having direction "dir"                  */

object_t *find_closest_object(
list_t   *list,        /* Object list       */
vec_t    *base,        /* Base of ray       */
vec_t    *dir,         /* direction of ray  */
object_t *last_hit,    /* object last hit   */
double   *retdist);

void object_dump(
FILE *out,
list_t *list);

/* == parser.c == */

/* Generalized attribute parser */
/* It returns a bit mask in which each possible attribute */
/* is represented by a bit on exit the attributes that    */
/* have been found will have their bit = 1                */

int parser(
FILE    *in,
pparm_t *pct,         /* parser control table                */
int      numattrs,    /* number of legal attributes          */
int      attrmax);
