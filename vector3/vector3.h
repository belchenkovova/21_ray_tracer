#ifndef VECTOR3_H
# define VECTOR3_H

# include "math.h"

typedef struct 			s_vector3
{
	float 				x;
	float 				y;
	float 				z;
}						t_vector3;

# define VECTOR3_REF	const t_vector3 *

t_vector3				vector3_add_ref(VECTOR3_REF, VECTOR3_REF);
t_vector3				vector3_add_cp(t_vector3, t_vector3);
void					vector3_add_eq_ref(t_vector3 *, VECTOR3_REF);
void					vector3_add_eq_cp(t_vector3 *, t_vector3);

t_vector3				vector3_sub_ref(VECTOR3_REF, VECTOR3_REF);
t_vector3				vector3_sub_cp(t_vector3, t_vector3);
void					vector3_sub_eq_ref(t_vector3 *, VECTOR3_REF);
void					vector3_sub_eq_cp(t_vector3 *, t_vector3);

t_vector3				vector3_mul_ref(VECTOR3_REF, float);
t_vector3				vector3_mul_cp(t_vector3, float);
void					vector3_mul_eq(t_vector3 *, float);

t_vector3				vector3_div_ref(VECTOR3_REF v, float f);
t_vector3				vector3_div_cp(t_vector3 v, float f);
void					vector3_div_eq(t_vector3 *v, float f);

float 					vector3_dot_ref(VECTOR3_REF, VECTOR3_REF);
float 					vector3_dot_cp(t_vector3, t_vector3);

t_vector3				vector3_cross_ref(VECTOR3_REF, VECTOR3_REF);
t_vector3				vector3_cross_cp(t_vector3, t_vector3);

float 					vector3_length_ref(VECTOR3_REF);
float 					vector3_length_cp(t_vector3);

void					vector3_normalize(t_vector3 *);
t_vector3				vector3_normalized_ref(VECTOR3_REF);
t_vector3				vector3_normalized_cp(t_vector3);

float 					vector3_max(VECTOR3_REF v);
float 					vector3_min(VECTOR3_REF v);

#endif
