#ifndef __HITABLE_OBJECTS_H__
#define __HITABLE_OBJECTS_H__

#include <stdbool.h>
#include "vector3.h"
#include "color.h"

enum {
	RT_SHAPE_SPHERE,
	RT_SHAPE_RECTANGLE
};

enum {
	LAMBERTIAN,
	METAL,
	GLASS
} MATERIAL_TYPE;

typedef struct {
	point3_t center;
	float radius;
} sphere_t;

typedef struct {
        float x0;
        float y0;
        float x1;
        float y1;
        float k;
} rectangle_t;

struct rt_obj {
	int hittable_type;
	sphere_t sphere;
	rectangle_t rectangle;

	color_t albedo;

	int material;
	float metal_fuzzyness;
	float glass_ir; //index of refraction
	float light_attenuation;

	struct rt_obj *next;
};

typedef struct {
	point3_t orig;
	vec3_t dir;
} ray_t;

typedef struct {
	point3_t p;
	vec3_t normal;
	float u, v;
	float t;
	bool front_face;
} hit_record_t;

/* shape setters */
void rt_object_set_sphere_shape(struct rt_obj *new_obj,
	float center_x, float center_y, float center_z, float radius);
void rt_object_set_rectangle_shape(struct rt_obj *obj,
        float x0, float y0, float x1, float y1, float k);

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
