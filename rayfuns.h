/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 9, 2009
 * Program 5
 *
 * Description
 * Returns the index of the target string in the
 * table of string pointers. return -1 on failure
 ***********************************************************************/
 
/* rayfuns.h */

static inline int table_lookup(
char *idtab[],
int  count,
char *target)
{
   int i;

   int rc = -1;

   for (i = 0; i < count; i++)
   {
      if (strcmp(target, idtab[i]) == 0)
         return(i);
   }
   return(rc);
}

static inline int getndxp(
pparm_t *parsetab,
int     count,        /* number of attributes     */
char *target)         /* candidate attribute name */
{
   int i;
   pparm_t *ppe = parsetab;

   int rc = -1;

   for (i = 0; i < count; i++)
   {

      if (strcmp(target, ppe->attrname) == 0)
         return(i);
      ppe += 1;
   }
   return(rc);
}

/* Computer p2 = s * p1 where s is a scalar */

static inline void pix_scale(
double  s,
drgb_t  *p1,
drgb_t  *p2)
{
   p2->r = s * p1->r;
   p2->g = s * p1->g;
   p2->b = s * p1->b;
}

/* Compute componentwise product of two rgb values */

static inline void pix_prod(
drgb_t  *p1,
drgb_t  *p2,
drgb_t  *p3)
{
   p3->r = p1->r * p2->r;
   p3->g = p1->g * p2->g;
   p3->b = p1->b * p2->b;
}

/* Compute componentwise sum of two rgb values */

static inline void pix_sum(
drgb_t  *p1,
drgb_t  *p2,
drgb_t  *p3)
{
   p3->r = p1->r + p2->r;
   p3->g = p1->g + p2->g;
   p3->b = p1->b + p2->b;
}

/* Compute componentwise sum of two rgb values */

static inline void pix_copy(
drgb_t  *p1,
drgb_t  *p2)
{
   p2->r = p1->r;
   p2->g = p1->g;
   p2->b = p1->b;
}


