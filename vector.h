/**********************************************************************
 * Kevin Matthew Smith && Burns John Hudson
 * kevin4 && burnsh
 * CpSc 102 Section 003
 * March 25, 2009
 * Program 6
 *
 * Description
 * This header file contains vector definitions and inline functions
 * for 3 - D vector and matrix operations              
 ***********************************************************************/
 
/* vector.h */

typedef struct vec_type
{
   double x;
   double y;
   double z;
}  vec_t;

typedef struct matrix_type
{
   vec_t row[3];
}  mat_t;

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

/**/
/* Compute the outer product of two input vectors */

static inline void vec_cross(
vec_t *v1,         /* Left input vector  */
vec_t *v2,         /* Right input vector */
vec_t *v3)         /* Output vector      */
{
	vec_t t;

	t.x = v1->y * v2->z - v1->z * v2->y;
	t.y = v1->z * v2->x - v1->x * v2->z;
	t.z = v1->x * v2->y - v1->y * v2->x;

	vec_copy(&t, v3);
}

/**/
/* project a vector onto a plane */

static inline void vec_project(
vec_t *n,        /* plane normal     */
vec_t *v,        /* input vector     */
vec_t *p)        /* projected vector */
{
   vec_t   temp;
   double  ndotv;

   ndotv = vec_dot(n, v);
   vec_scale(ndotv, n, &temp);
   vec_diff(&temp, v, p);
}

/**/
/* reflect a vector from a surface plane */

static inline void vec_reflect(
vec_t *n,        /* surface normal          */
vec_t *w,        /* incoming ray vector     */
vec_t *v)       /* reflected vector        */
{
	double udotn;
	vec_t u, sn, f;

	vec_scale(-1,w,&u);
	vec_scale(2,n,&sn);
	udotn = vec_dot(&u, n);
	vec_scale(udotn, &sn, &f);
	vec_diff(&u, &f, v);
}

/* Apply transform matrix to vector */

static inline void vec_xform(
mat_t *m,
vec_t *v1,
vec_t *v2)
{
	vec_t t;

	t.x = vec_dot(&m->row[0], v1);
	t.y = vec_dot(&m->row[1], v1);
	t.z = vec_dot(&m->row[2], v1);

	vec_copy(&t, v2);
}

/* Compute the transpose of a matrix */

static inline void mat_transpose(
mat_t *m1,
mat_t *m2)
{
	mat_t t;

	t.row[0].x = m1->row[0].x;
	t.row[0].y = m1->row[1].x;
	t.row[0].z = m1->row[2].x;

	t.row[1].x = m1->row[0].y;
	t.row[1].y = m1->row[1].y;
	t.row[1].z = m1->row[2].y;

	t.row[2].x = m1->row[0].z;
	t.row[2].y = m1->row[1].z;
	t.row[2].z = m1->row[2].z;
	
	vec_copy(&t.row[0], &m2->row[0]);
	vec_copy(&t.row[1], &m2->row[1]);
	vec_copy(&t.row[2], &m2->row[2]);
}

static inline void mat_multiply(
mat_t *m1)
{
	m1->row[1].x = m1->row[2].x * m1->row[0].x;
	m1->row[1].y = m1->row[2].y * m1->row[0].y;
	m1->row[1].z = m1->row[2].z * m1->row[0].z;
}
