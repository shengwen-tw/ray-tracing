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

void vec3_random_unit_vector(vec3_t *vec)
{
	float a = clamped_random_float(0.0f, 2.0f * M_PI);
	float z = clamped_random_float(-1.0f, 1.0f);
	float r = sqrt(1.0f - (z * z));

	vec->e[0] = r * cos(a);
	vec->e[1] = r * sin(a);
	vec->e[2] = z;
}

void vec3_random_in_hemisphere(vec3_t *random_vec, vec3_t *normal)
{
	vec3_random_in_unit_sphere(random_vec);

	if(vec3_dot_product(random_vec, normal) > 0.0f) {
		//in the hemisphere as the normal
		return;
	} else {
		//flip sign
		random_vec->e[0] *= -1.0f;
		random_vec->e[1] *= -1.0f;
		random_vec->e[2] *= -1.0f;
		return;
	}
}

void vec3_reflect(vec3_t *vec_in, vec3_t *normal, vec3_t *vec_reflect)
{
	float float_tmp;
	vec3_t vec_tmp;
	float_tmp = 2.0f * vec3_dot_product(vec_in, normal);
	vec3_scaling(float_tmp, normal, &vec_tmp);
	vec3_sub(vec_in, &vec_tmp, vec_reflect);
}

void vec3_refract(vec3_t *uv, vec3_t *n, float etai_over_etat, vec3_t *refract_vec)
{
	vec3_t neg_uv;
	vec3_negate(uv, &neg_uv);

	float cos_theta = vec3_dot_product(&neg_uv, n);

	vec3_t n_cos_theta, vec_tmp, r_out_prep;
	vec3_scaling(cos_theta, n, &n_cos_theta);
	vec3_add(uv, &n_cos_theta, &vec_tmp);
	vec3_scaling(etai_over_etat, &vec_tmp, &r_out_prep);

	vec3_t r_out_parallel;
	vec3_scaling(-sqrt(fabs(1.0f - vec3_length_squared(&r_out_prep))), n, &r_out_parallel);

	vec3_add(&r_out_prep, &r_out_parallel, refract_vec);
}
