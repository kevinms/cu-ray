/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 25, 2009
 * Program 6
 *
 * Description
 * Loads the values of the specified attribute
 ***********************************************************************/
 
/* parser.c */

#include "ray.h"

static int parser_load_attr(
FILE    *in,
pparm_t *pct,        /* parser control table       */
int     numattrs,    /* number of legal attributes */
char    *attrname)   /* attribute name             */
{
   pparm_t *pce;     /* Entry corresponding to this attribute */
   int     count = 0;
   unsigned char *loc;
   int     ndx;
   int     i;

/* getndxp is an updated version of getndx that takes a parse */
/* control table pointer as input.                            */

   ndx = getndxp(pct, numattrs, attrname);
   assert(ndx >= 0);

/* Point to the proper entry in the table */

   pce = pct + ndx;

/* pce->loc points to where the first value must go */

   loc = (unsigned char *) pce->loc;

/* Attributes may have different numbers of attribute values */
/* for example the viewpoint has three but the pixeldim only */
/* has 2 values                                              */

   for (i = 0; i < pce->numvals; i++)
   {
      count += fscanf(in, pce->fmtstr, loc);
   // double  *work;
   // work = (double *)loc;
   // fprintf(stderr, "%s %lf \n", pce->attrname, *work);
      loc += pce->valsize;
   }
   assert(count == pce->numvals);
   return(ndx);

}

/**/
/* Generalized attribute parser */
/* It returns a bit mask in which each possible attribute */
/* is represented by a bit on exit the attributes that    */
/* have been found will have their bit = 1                */

int parser(
FILE    *in,
pparm_t *pct,         /* parser control table                */
int      numattrs,    /* number of legal attributes          */
int      attrmax)     /* Quit after this many attrs if not 0 */
{
   char attrname[NAME_LEN];
   int  attrcount;
   int  mask;
   int  ndx;

   attrcount = 0;
   mask = 0;
   fscanf(in, "%s", attrname);

/* One trip is made through this loop for every attribute */
/* processed... Exit from the loop is triggered by '}'    */
/* or if the maximum number of attributes is set, when    */
/* the maximum number have been processed                 */

   while (strlen(attrname) && attrname[0] != '}')
   {

   /* Process one attribute */

      ndx = parser_load_attr(in, pct, numattrs, attrname);

      mask |= 1 << ndx;
      attrcount++;

   /* See if its quitting time */

      if ((attrmax) && (attrcount == attrmax))
         break;

      *attrname = 0;
      fscanf(in, "%s", attrname);
   }

   if (attrmax != attrcount)
      assert(attrname[0] == '}');

   return(mask);
}
