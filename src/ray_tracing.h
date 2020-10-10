#ifndef __RAY_H__
#define __RAY_H__

#include <stdbool.h>
#include "vector3.h"
#include "color.h"
#include "rt_objects.h"

void set_face_normal(hit_record_t *rec, ray_t *ray, vec3_t *outward_normal);

void ray_init(ray_t *ray, vec3_t *origin, vec3_t *direction);
void ray_at(ray_t *ray, float t, point3_t *point_result);
void ray_color(ray_t *ray, color_t *pixel_color, int depth);

bool sphere_hit(sphere_t *sphere, ray_t *ray, float t_min, float t_max, hit_record_t *rec);
bool rectangle_hit(rectangle_t *rectangle, ray_t *ray, float t0, float t1,
                   hit_record_t *rec);

#endif
