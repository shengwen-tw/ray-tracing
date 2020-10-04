#ifndef __MATERIALS_H__
#define __MATERIALS_H__

#include "ray.h"

enum {
	LAMBERTIAN,
	METAL,
} MATERIAL_TYPE;

bool lambertian_scattering(ray_t *ray_in, hit_record_t *rec, ray_t *scattered_ray);
bool metal_scattering(ray_t *ray_in, hit_record_t *rec, ray_t *scattered_ray, float fuzzyness);

#endif
