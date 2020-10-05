#ifndef __HITABLE_OBJECTS_H__
#define __HITABLE_OBJECTS_H__

#include "vector3.h"
#include "ray_tracing.h"

enum {
	HITTALBE_TYPE_SPHERE
};

struct rt_obj {
	int hittable_type;
	sphere_t sphere;

	color_t albedo;

	int material;
	float metal_fuzzyness;
	float glass_ir; //index of refraction
	float light_attenuation;

	struct rt_obj *next;
};

/* shape setters */
void rt_object_set_sphere_shape(struct rt_obj *new_obj,
	float center_x, float center_y, float center_z, float radius);

/* material setters */
void rt_object_set_difuse_material(struct rt_obj *obj,
        float albedo_red, float albedo_green, float albedo_blue);
void rt_object_set_metal_material(struct rt_obj *obj,
        float albedo_red, float albedo_green, float albedo_blue, float fuzzyness);
void rt_object_set_glass_material(struct rt_obj *obj, float index_of_refraction);

void rt_object_list_clear(void);
void rt_object_list_add(struct rt_obj *new_obj);

bool rt_object_list_hit(ray_t *ray, float t_min, float t_max, hit_record_t *rec,
                        struct rt_obj **hit_obj);

#endif
