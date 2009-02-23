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
    v3->x = v1->x + v2->x;
    v3->y = v1->y + v2->y;
    v3->z = v1->z + v2->z;
}

static inline void drgb_copy(
drgb_t *v1,
drgb_t *v2)
{
    v2->x = v1->x;
    v2->y = v1->y;
    v2->z = v1->z;
}

static inline void drgb_scale(
double s,
drgb_t  *v1,
drgb_t  *v2)
{
    v2->x = v1->x * s;
    v2->y = v1->y * s;
    v2->z = v1->z * s;
}

