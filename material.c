/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * February 9, 2009
 * Program 3
 *
 * Description
 * This program alocates memory for a material structure and parses and
 * loads the data for the structure.  Also a material_dump() function.
 ***********************************************************************/


#include "ray.h"

static char *mat_attrs[] = { "ambient", "diffuse", "specular" };
#define NUM_ATTRS (sizeof(mat_attrs) / sizeof(char *))

static inline void mat_load_ambient(FILE *in, material_t *mat)
{
   int count;
   assert(mat->cookie == MAT_COOKIE);
   count = fscanf(in, "%lf %lf %lf",
                  &mat->ambient.r, &mat->ambient.g,
                  &mat->ambient.b);
/* ensure that the required number of values were found */
   assert(count == 3);
}

static inline void mat_load_diffuse(FILE *in, material_t *mat)
{
   int count;
   assert(mat->cookie == MAT_COOKIE);
   count = fscanf(in, "%lf %lf %lf",
                  &mat->diffuse.r, &mat->diffuse.g,
                  &mat->diffuse.b);
/* ensure that the required number of values were found */
   assert(count == 3);
}

static inline void mat_load_specular(FILE *in, material_t *mat)
{
   int count;
   assert(mat->cookie == MAT_COOKIE);
   count = fscanf(in, "%lf %lf %lf",
                  &mat->specular.r, &mat->specular.g,
                  &mat->specular.b);
/* ensure that the required number of values were found */
   assert(count == 3);
}

static int material_attr_load(
FILE      *in,
material_t *mat,       /* material to be filled in */
char      *attrname)
{
	int ndx;

	assert(mat->cookie = MAT_COOKIE);

	ndx = table_lookup(mat_attrs, NUM_ATTRS, attrname);
	assert(ndx >= 0);
	switch(ndx)
	{
		case 0:
			mat_load_ambient(in, mat); return 0;
		case 1:
			mat_load_diffuse(in, mat); return 0;
		case 2:
			mat_load_specular(in, mat); return 0;
		default:
			return -1;
	}
}

/* Create a new material description */
void material_init(
FILE       *in,
model_t    *model,
int        attrmax)
{
	material_t *mat = NULL;
	char attrname[NAME_LEN];
	int count;
	
	mat = (material_t *)malloc(sizeof(material_t));
	assert(mat != NULL);
	memset(mat, 0, sizeof(mat));
	mat->cookie = MAT_COOKIE;

	assert(fscanf(in, "%s", mat->name) == 1);

	fscanf(in, "%s", attrname);
	assert(attrname[0] == '{');

	count = fscanf(in, "%s", attrname);
	assert(count == 1 && attrname[0] != '}');
	while( (count == 1) && (attrname[0] != '}') )
	{
		assert(material_attr_load(in, mat, attrname) == 0);
		*attrname = 0;
		fscanf(in, "%s", attrname);
	}

	assert(attrname[0] == '}');

	list_add(model->mats, mat);
}


/* Produce a formatted dump of the material list */
void material_dump(
FILE *out,
model_t *model)
{
	list_t *templist = NULL;
	link_t *templink = NULL;
	material_t *tempmat = NULL;

	templist = model->mats;
	templink = templist->head;

	while(templink != NULL)
	{
		tempmat = (material_t *)templink->item;
		fprintf(stderr, "material     %s \n", tempmat->name);
		fprintf(stderr, "ambient %10.1lf %5.1lf %5.1lf \n",
                        tempmat->ambient.r, 
						tempmat->ambient.g, 
						tempmat->ambient.b);
		fprintf(stderr, "diffuse %10.1lf %5.1lf %5.1lf \n",
                        tempmat->diffuse.r, 
						tempmat->diffuse.g, 
						tempmat->diffuse.b);
		fprintf(stderr, "specular %9.1lf %5.1lf %5.1lf \n\n",
                        tempmat->specular.r, 
						tempmat->specular.g, 
						tempmat->specular.b);
		
		templink = templink->next;
	}
}


/* Search the material list looking for a material */
/* having the specified color name. If found,      */
/* return the address of the material_t structure  */
/* If not, found return NULL                        */

material_t *material_search(
model_t *model,
char    *name)     // e.g. orange
{
	list_t *templist = NULL;
	link_t *templink = NULL;
	material_t *tempmat = NULL;

	templist = model->mats;
	templink = templist->head;

	while(templink != NULL)
	{
		tempmat = (material_t *)templink->item;

		if( strcmp(tempmat->name, name) == 0 )
			return tempmat;

		templink = templink->next;
	}
	return NULL;
}
