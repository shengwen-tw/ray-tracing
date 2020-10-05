#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vector3.h"
#include "ray_tracing.h"

typedef struct {
	point3_t origin;
	point3_t lower_left_corner;
	vec3_t horizontal;
	vec3_t vertical;
} camera_t;

void camera_set_default(camera_t *camera);
void camera_set(camera_t *camera, point3_t *look_from, point3_t *look_at,
                vec3_t *vup, float vfov, float aspect_ratio);

void camera_get_ray(camera_t *camera, ray_t *ray, float u, float v);

#endif
