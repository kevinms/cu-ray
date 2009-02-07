#include "ray.h"

object_t    *object_init(
FILE        *in,
model_t     *model)
{
   object_t    *obj;
   material_t *mat;
   char buf[NAME_LEN];
   int count;
/* Create a new object structure and zero it */
   obj = malloc(sizeof(object_t));
   assert(obj != NULL);
   memset(obj, 0, sizeof(object_t));
   obj->cookie = OBJ_COOKIE;
/* Read the descriptive name of the object */
/* left_wall, center_sphere, etc.          */
   count = fscanf(in, "%s", obj->objname);
   assert(count == 1);
/* Consume the delimiter */
   count = fscanf(in, "%s", buf);
   assert(buf[0] == '{');
/* First attribute must be material */
   count = fscanf(in, "%s", buf);
   assert(count == 1);
   count = strcmp(buf, "material");
   assert(count == 0);
   count = fscanf(in, "%s", buf);
   assert(count == 1);
   mat = material_search(model, buf);
   assert(mat != NULL);
   obj->mat = mat;
   list_add(model->objs, (void *)obj);
   return(obj);
}

/**/
void object_dump(
FILE *out,
model_t *model)
{
	list_t *templist;
	link_t *templink;
	object_t *obj;

	templist = model->objs;
	templink = templist->head;

	while(templink != NULL)
	{
		obj = (object_t *)templink->item;

		fprintf(out, "%s       %s\n", obj->objtype, obj->objname);
		fprintf(out, "material     %s\n", obj->mat->name);
		obj->dumper(out, obj);
		templink = templink->next;
	}
}
