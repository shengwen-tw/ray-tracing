#ifndef __MATERIALS_H__
#define __MATERIALS_H__

#include "ray.h"

enum {
	LAMBERTIAN,
	METAL,
} MATERIAL_TYPE;

void scatter(ray_t *ray_in, hit_record_t *rec, color_t *attenuation, ray_t *scattered);

#endif
