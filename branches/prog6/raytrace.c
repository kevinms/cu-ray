/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 9, 2009
 * Program 5
 *
 * Description
 * Find the closest object intersection on the ray based
 * at "base" and having direction "dir" 
 ***********************************************************************/
 
/* raytrace.c */

#include "ray.h"

extern int hitid;
extern int pix_x, pix_y;


object_t *find_closest_object(
list_t   *list,        /* Object list       */
vec_t    *base,        /* Base of ray       */
vec_t    *dir,         /* direction of ray  */
object_t *last_hit,    /* object last hit   */
double   *retdist)     /* dist to hit point */
{
   double    dist;
   object_t  *closest = NULL;
   double    mindist;
   object_t  *obj =  (object_t *)list->start();

   while (obj != NULL)
   {
      if (obj == last_hit)
      {
         obj = (object_t *)list->get_next();
         continue;
      }

      dist = obj->hits(base, dir);

#ifdef DBG_FIND
      fprintf(stderr, "FND %12s: %5.1lf - \n ",
                                  obj->objname, dist);
#endif

   /* see if this is first obj it or closest hit */
   /* and in that case update closest            */

      if ((dist >= 0) && ((closest == NULL) || (dist < mindist)))
      {
          mindist = dist;
          closest = obj;
      }
      obj = (object_t *)list->get_next();
   }

   *retdist = mindist;
   return(closest);
}

/**/
/* This function traces a single ray and returns the composite */
/* intensity of the light it encounters                        */

void ray_trace(
model_t  *model,
vec_t    *base,        /* location of viewer or previous hit */
vec_t    *dir,         /* unit vector in direction of object */
drgb_t   *pix,         /* pixel     return location          */
double   total_dist,   /* distance ray has traveled so far   */
object_t *last_hit)    /* most recently hit object           */
{
   object_t *closest;
// drgb_t   specular = {0.0, 0.0, 0.0};
   double   mindist;
   drgb_t   thisray = {0.0, 0.0, 0.0};

/* Need to disable infinite ray ping pong in specular cases */

   if (total_dist > MAX_DIST)
      return;

   closest = find_closest_object(model->objs,
                                 base, dir, last_hit, &mindist);

   if (closest == NULL)
      return;

#ifdef DBG_HIT
   fprintf(stderr, "%-12s (%5.1lf, %5.1lf, %5.1lf)",
                     closest->objname,
                     closest->hitloc.x, closest->hitloc.y,
                     closest->hitloc.z);
#endif

   total_dist += mindist;

#if 0
   if (closest->objtype == REF_SPHERE)
   {
      double newbase[3];
      double newdir[3];
      total_dist += refsphere_bounce(closest, dir, newbase, newdir);
      ray_trace(model, newbase, newdir, intensity, total_dist, closest);
      return;
   }
#endif

/* Hit object in scene, compute ambient and diffuse */
/* intensity of reflected light.                    */

   closest->getamb(&thisray);

/* illuminate(model, closest, &thisray); */

/* Scale intensity by distance of ray travel */

   pix_scale(1 / total_dist, &thisray, &thisray);
   pix_sum(&thisray, pix, pix);

#ifdef DBG_DRGB
   fprintf(stderr, "%-12s (%5.1lf, %5.1lf, %5.1lf)",
                     closest->objname, pix->r, pix->g, pix->b);
#endif
   return;

}

