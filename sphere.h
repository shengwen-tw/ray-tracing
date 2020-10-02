#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "vector3.h"
#include "ray.h"

typedef struct {
	point3_t center;
	float radius;
} sphere_t;

void sphere_init(sphere_t *sphere, point3_t *center, float r);
bool sphere_hit(sphere_t *sphere, ray_t *ray, float t_min, float t_max, hit_record_t *rec);

#endif
