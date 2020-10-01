#include <math.h>
#include <vector3.h>

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

void vec3_scaling(float factor, vec3_t *v, vec3_t *v_result)
{
	v_result->e[0] = v->e[0] * factor;
	v_result->e[1] = v->e[1] * factor;
	v_result->e[2] = v->e[2] * factor;
}

void vec3_divide(float factor, vec3_t *v, vec3_t *v_result)
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
