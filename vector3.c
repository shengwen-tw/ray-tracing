#include <stdio.h>
#include <math.h>
#include <vector3.h>
#include "common.h"

float vec3_assign(vec3_t *v_dest, vec3_t *v_src)
{
	v_dest->e[0] = v_src->e[0];
	v_dest->e[1] = v_src->e[1];
	v_dest->e[2] = v_src->e[2];
}

float vec3_set(vec3_t *v, float x, float y, float z)
{
	v->e[0] = x;
	v->e[1] = y;
	v->e[2] = z;
}

float vec3_get_x(vec3_t *v)
{
	return v->e[0];
}

float vec3_get_y(vec3_t *v)
{
	return v->e[1];
}

float vec3_get_z(vec3_t *v)
{
	return v->e[2];
}

void vec3_add(vec3_t *v1, vec3_t *v2, vec3_t *v_result)
{
	v_result->e[0] = v1->e[0] + v2->e[0];
	v_result->e[1] = v1->e[1] + v2->e[1];
	v_result->e[2] = v1->e[2] + v2->e[2];
}

void vec3_sub(vec3_t *v1, vec3_t *v2, vec3_t *v_result)
{
	v_result->e[0] = v1->e[0] - v2->e[0];
	v_result->e[1] = v1->e[1] - v2->e[1];
	v_result->e[2] = v1->e[2] - v2->e[2];
}

void vec3_scaling(float factor, vec3_t *v, vec3_t *v_result)
{
	v_result->e[0] = v->e[0] * factor;
	v_result->e[1] = v->e[1] * factor;
	v_result->e[2] = v->e[2] * factor;
}

void vec3_div(float factor, vec3_t *v, vec3_t *v_result)
{
	float div_factor = 1.0f / factor;

	v_result->e[0] = v->e[0] * div_factor;
	v_result->e[1] = v->e[1] * div_factor;
	v_result->e[2] = v->e[2] * div_factor;
}

void vec3_negate(vec3_t *v, vec3_t *v_result)
{
	v_result->e[0] = -v->e[0];
	v_result->e[1] = -v->e[1];
	v_result->e[2] = -v->e[2];
}

void vec3_element_wise_product(vec3_t *v1, vec3_t *v2, vec3_t *v_result)
{
	v_result->e[0] = v1->e[0] * v2->e[0];
	v_result->e[1] = v1->e[1] * v2->e[1];
	v_result->e[2] = v1->e[2] * v2->e[2];
}

float vec3_dot_product(vec3_t *v1, vec3_t *v2)
{
	return v1->e[0] * v2->e[0] +
               v1->e[1] * v2->e[1] +
               v1->e[2] * v2->e[2];
}

void vec3_cross_product(vec3_t *v1, vec3_t *v2, vec3_t *v_result)
{
	v_result->e[0] = v1->e[1] * v2->e[2] - v1->e[2] * v2->e[1];
	v_result->e[1] = v1->e[2] * v2->e[0] - v1->e[0] * v2->e[2];
	v_result->e[2] = v1->e[0] * v2->e[1] - v1->e[1] * v2->e[0];
}

void vec3_unit_vector(vec3_t *v, vec3_t *v_result)
{
	float div_len = 1.0f / vec3_length(v);

	v_result->e[0] = v->e[0] * div_len;
	v_result->e[1] = v->e[1] * div_len;
	v_result->e[2] = v->e[2] * div_len;
}

float vec3_length(vec3_t *v)
{
	return sqrt(v->e[0]*v->e[0] + v->e[1]*v->e[1] + v->e[2]*v->e[2]);
}

float vec3_length_squared(vec3_t *v)
{
	return v->e[0]*v->e[0] + v->e[1]*v->e[1] + v->e[2]*v->e[2];
}

void vec3_random(vec3_t *random_vec)
{
	random_vec->e[0] = random_float();
	random_vec->e[1] = random_float();
	random_vec->e[2] = random_float();
}

void vec3_clamped_random(vec3_t *random_vec, float min, float max)
{
	random_vec->e[0] = clamped_random_float(min, max);
	random_vec->e[1] = clamped_random_float(min, max);
	random_vec->e[2] = clamped_random_float(min, max);
}

void vec3_random_in_unit_sphere(vec3_t *vec)
{
	while(1) {
		vec3_clamped_random(vec, -1.0f, 1.0f);

		//fprintf(stderr, "%f\n", vec3_length(vec));

		if(vec3_length(vec) > 1.0f) {
			continue;
		} else {
			return;
		}
	}
}
