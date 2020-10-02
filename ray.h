#ifndef __RAY_H__
#define __RAY_H__

#include "vector3.h"
#include "color.h"

typedef struct {
	point3_t orig;
	vec3_t dir;
} ray_t;

typedef struct {
	point3_t p;
	vec3_t normal;
	double t;
} hit_record_t;

void ray_init(ray_t *ray, vec3_t *origin, vec3_t *direction);
void ray_get_origin(ray_t *ray, point3_t *orig);
void ray_get_direction(ray_t *ray, vec3_t *dir);
void ray_at(ray_t *ray, float t, point3_t *point_result);
void ray_color(ray_t *ray, color_t *pixel_color);

#endif
