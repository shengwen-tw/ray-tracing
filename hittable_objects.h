#ifndef __HITABLE_OBJECTS_H__
#define __HITABLE_OBJECTS_H__

#include "sphere.h"

enum {
	HITTALBE_TYPE_SPHERE
};

struct hittable_obj {
	int hittable_type;
	sphere_t sphere;
	int material;

	struct hittable_obj *next;
};

void hittalbe_object_sphere_init(struct hittable_obj *new_obj,
	float center_x, float center_y, float center_z, float radius, int material);

void hittable_list_clear(void);
void hittable_list_add(struct hittable_obj *new_obj);

bool hittable_list_hit(ray_t *ray, float t_min, float t_max, hit_record_t *rec);

#endif
