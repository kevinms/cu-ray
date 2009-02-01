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




