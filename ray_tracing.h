#ifndef __RAY_H__
#define __RAY_H__

#include <stdbool.h>
#include "vector3.h"
#include "color.h"

enum {
        LAMBERTIAN,
        METAL,
	GLASS
} MATERIAL_TYPE;

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

void set_face_normal(hit_record_t *rec, ray_t *ray, vec3_t *outward_normal);

void ray_init(ray_t *ray, vec3_t *origin, vec3_t *direction);
void ray_at(ray_t *ray, float t, point3_t *point_result);
void ray_color(ray_t *ray, color_t *pixel_color, int depth);

bool sphere_hit(sphere_t *sphere, ray_t *ray, float t_min, float t_max, hit_record_t *rec);
bool rectangle_hit(rectangle_t *rectangle, ray_t *ray, float t0, float t1,
                   hit_record_t *rec);

#endif
