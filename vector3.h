#ifndef __VECTOR3_H__
#define __VECTOR3_H__

typedef struct {
	float e[3];
} vec3_t;

float vec3_assign(vec3_t *v_dest, vec3_t *v_src);
float vec3_set(vec3_t *v, float x, float y, float z);
float vec3_get_x(vec3_t *v);
float vec3_get_y(vec3_t *v);
float vec3_get_z(vec3_t *v);
void vec3_add(vec3_t *v1, vec3_t *v2, vec3_t *v_result);
void vec3_sub(vec3_t *v1, vec3_t *v2, vec3_t *v_result);
void vec3_scaling(float factor, vec3_t *v, vec3_t *v_result);
void vec3_div(float factor, vec3_t *v, vec3_t *v_result);
void vec3_negate(vec3_t *v, vec3_t *v_result);
void vec3_element_wise_product(vec3_t *v1, vec3_t *v2, vec3_t *v_result);
float vec3_dot_product(vec3_t *v1, vec3_t *v2);
void vec3_cross_product(vec3_t *v1, vec3_t *v2, vec3_t *v_result);
void vec3_unit_vector(vec3_t *v, vec3_t *v_result);
float vec3_length(vec3_t *v);
float vec3_length_squared(vec3_t *v);

typedef vec3_t point3_t;

#endif
