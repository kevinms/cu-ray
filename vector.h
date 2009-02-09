/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * February 9, 2009
 * Program 3
 *
 * Description
 * This header file contains vector definitions and inline functions for
 * 3-D vector and matrix operations
 ***********************************************************************/

/* vector.h */

/* This header file contains vector definitions and */
/* inline functions for 3 - D vector and matrix     */
/* operations                                       */

/* Three dimensional coordinate structures */

typedef struct vec_type
{
   double x;
   double y;
   double z;
}  vec_t;

/**/
/* Compute the vector sum  v3 = v2 + v1 */

static inline void vec_sum(
vec_t  *v1,        /* Left input vector  */
vec_t  *v2,        /* Right input vector */
vec_t  *v3)        /* Output vector      */
{
	v3->x = v1->x + v2->x;
	v3->y = v1->y + v2->y;
	v3->z = v1->z + v2->z;
}

/**/
/* Copy vector v1 to vector v2 */

static inline void vec_copy(
vec_t *v1,
vec_t *v2)
{
	v2->x = v1->x;
	v2->y = v1->y;
	v2->z = v1->z;
}

/**/
/* Compute the vector difference  v3 = v2 - v1 */

static inline void vec_diff(
vec_t  *v1,        /* Left input vector  */
vec_t  *v2,        /* Right input vector */
vec_t  *v3)        /* Output vector      */
{
	v3->x = v2->x - v1->x;
	v3->y = v2->y - v1->y;
	v3->z = v2->z - v1->z;
}

/**/
/* Compute the inner product dot = v1 dot v2 */

static inline double vec_dot(
vec_t *v1,
vec_t *v2)
{
	return ((v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z));
}

/**/
/* Compute the length of the vector v1   */

static inline double vec_len(
vec_t  *v1)   /* Input vector  */
{
	return sqrt(vec_dot(v1, v1));
}

/* Computer v2 = s * v1 where s is a scalar */

static inline void vec_scale(
double s,
vec_t  *v1,
vec_t  *v2)
{
	v2->x = v1->x * s;
	v2->y = v1->y * s;
	v2->z = v1->z * s;
}

/**/
/* Compute v2 = a unit length vector in the direction of v1 */

static inline void vec_unit(
vec_t *v1,
vec_t *v2)
{
	vec_scale((1.0 / vec_len(v1)), v1, v2);
}


static inline int vec_load(
FILE  *in,
vec_t *v1)   /* vector to be read in */
{
	return fscanf(in, "%lf %lf %lf \n", &v1->x, &v1->y, &v1->z);
}

/**/
/* Print the contents of a vector */

static inline void vec_prn(
FILE  *out,
char  *label,   /* label string    */
vec_t *v1)     /* vector to print */
{
	fprintf(out, "%s %8.3lf %8.3lf %8.3lf \n", label, v1->x, v1->y, v1->z);
}
