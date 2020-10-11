#ifndef __RAY_H__
#define __RAY_H__

#include <stdint.h>
#include <stdbool.h>
#include "vector3.h"
#include "color.h"
#include "rt_objects.h"

enum {
	BACKGROUND_LIGHT_USE_DEFAULT,
	BACKGROUND_LIGHT_USE_ASSIGNED_COLOR,
} BACKGROUND_LIGHT_MODE;

/* background */
void rt_set_background_light_color(float r, float g, float b);
void rt_set_use_default_background_light(void);

void set_face_normal(hit_record_t *rec, ray_t *ray, vec3_t *outward_normal);

void ray_init(ray_t *ray, vec3_t *origin, vec3_t *direction);
void ray_at(ray_t *ray, float t, point3_t *point_result);
void ray_color(ray_t *ray, color_t *pixel_color, float u, float v, int depth);

bool sphere_hit(sphere_t *sphere, ray_t *ray, float t_min, float t_max, hit_record_t *rec);
bool rectangle_hit(rectangle_t *rectangle, ray_t *ray, float t0, float t1,
                   hit_record_t *rec);

#endif
