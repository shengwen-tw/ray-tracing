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
	RECTANGLE_XY_PLANE,
	RECTANGLE_XZ_PLANE,
	RECTANGLE_YZ_PLANE
} RECTANGLE_PLANE_FIRECTION;

enum {
	LAMBERTIAN,
	METAL,
	GLASS,
} MATERIAL_TYPE;

typedef struct {
	point3_t center;
	float radius;
} sphere_t;

typedef struct {
	float x0, y0, z0;
	float x1, y1, z1;
        float k;

	int plane;
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

	/* light emision from the object */
	bool emit_light;
	color_t emit_light_color;

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
void rt_object_set_rectangle_shape(struct rt_obj *obj, int plane,
        float x0, float y0, float z0,
	float x1, float y1, float z1,
	float k);

/* material setters */
void rt_object_set_difuse_material(struct rt_obj *obj,
        float albedo_red, float albedo_green, float albedo_blue);
void rt_object_set_metal_material(struct rt_obj *obj,
        float albedo_red, float albedo_green, float albedo_blue, float fuzzyness);
void rt_object_set_glass_material(struct rt_obj *obj, float index_of_refraction);

/* light emission property */
void rt_object_set_light_emmision(struct rt_obj *obj, bool obj_emit_light,
                                  float emit_color_r, float emit_color_g,
                                  float emit_color_b);

void rt_object_list_clear(void);
void rt_object_list_add(struct rt_obj *new_obj);

bool rt_object_list_hit(ray_t *ray, float t_min, float t_max, hit_record_t *rec,
                        struct rt_obj **hit_obj);

#endif
