/* rayfuns.h */

/**/
/* return the index of the target string in the   */
/* table of string pointers. return -1 on failure */

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

static inline void drgb_sum(
drgb_t  *v1,
drgb_t  *v2,
drgb_t  *v3)
{
    v3->r = v1->r + v2->r;
    v3->g = v1->g + v2->g;
    v3->b = v1->b + v2->b;
}

static inline void drgb_copy(
drgb_t *v1,
drgb_t *v2)
{
    v2->r = v1->r;
    v2->g = v1->g;
    v2->b = v1->b;
}

static inline void drgb_scale(
double s,
drgb_t  *v1,
drgb_t  *v2)
{
    v2->r = v1->r * s;
    v2->g = v1->g * s;
    v2->b = v1->b * s;
}

