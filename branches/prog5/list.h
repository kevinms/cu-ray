
class link_t
{
public:
   link_t(void);                  // default constructor
   link_t(void *);                // overloaded constructor
   ~link_t (void);                // destructor
   void    set_next(link_t *);    // used in adding new link
   link_t *get_next(void);        // retrieve the next pointer
   void   *get_entity(void);      // retrieve entity pointer

private:
   link_t *next;                  // next link in the list
   void   *entity;                // entity managed by link
};

class list_t
{
public:
   list_t(void);                  // constructor
   ~list_t (void);                // destructor
   void   add(void *);            // add entity to end of list
   void   insert(void *);         // insert entity before current
   void   remove(void );          // remove current entity
   void   *start(void);           // set current to start of list
   void   *get_next(void);        // advance to next element in list

private:
   link_t *first;                 // first link
   link_t *last;                  // last link
   link_t *current;               // current link.
};

