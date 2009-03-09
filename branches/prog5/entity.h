#define NAME_LEN 16

#include <string.h>
#include <stdio.h>
/* A meaningless structure to put on the list */

class e_t
{
public:
    e_t(char *txt, int len)
    {
       strcpy(ename, txt);
       ecount = len;
    }
   ~e_t(void){ printf("destroying e_t    at %p \n", this); }

   void eprint()
   {
      printf("%-12s %6d \n", ename, ecount);
   }
private:
   char ename[NAME_LEN];    // entity name
   int  ecount;             // number of entities
};

