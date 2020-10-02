#include "vector3.h"
#include "ray.h"
#include "camera.h"

void camera_init(camera_t *camera)
{
	float aspect_ratio = 16.0 / 9.0;

	float viewport_height = 2.0f;
	float viewport_width = aspect_ratio * viewport_height;

	float focal_length = 1.0f;
	vec3_t vec_focal_length;
	vec3_set(&vec_focal_length, 0.0f, 0.0f, focal_length);

	vec3_set(&camera->origin, 0.0f, 0.0f, 0.0f);

	vec3_t half_horizontal;
	vec3_set(&camera->horizontal, viewport_width, 0.0f, 0.0f);
	vec3_scaling(0.5f, &camera->horizontal, &half_horizontal);

	vec3_t half_vertical;
	vec3_set(&camera->vertical, 0.0f, viewport_height, 0.0f);
	vec3_scaling(0.5f, &camera->vertical, &half_vertical);

	//lower_left_corner = origin - horizontal/2 - vertical/2 - (0, 0, focal_length)
	vec3_t lower_left_corner, tmp1, tmp2;
	vec3_sub(&camera->origin, &half_horizontal, &tmp1);
	vec3_sub(&tmp1, &half_vertical, &tmp2);
	vec3_sub(&tmp2, &vec_focal_length, &camera->lower_left_corner);
}

void camera_get_ray(camera_t *camera, ray_t *ray, float u, float v)
{
	//ray_direction = lower_left_corner + u*horizontal + v*horizontal - origin
	vec3_t ray_direction, u_horizontal, v_vertical, tmp1, tmp2;
	vec3_scaling(u, &camera->horizontal, &u_horizontal);
	vec3_scaling(v, &camera->vertical, &v_vertical);
	vec3_add(&camera->lower_left_corner, &u_horizontal, &tmp1);
	vec3_add(&tmp1, &v_vertical, &tmp2);
	vec3_sub(&tmp2, &camera->origin, &ray_direction);

	ray_init(ray, &camera->origin, &ray_direction);	
}
