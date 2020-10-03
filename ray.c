#include <stdbool.h>
#include <math.h>
#include "ray.h"
#include "color.h"
#include "hittable_objects.h"

void ray_init(ray_t *ray, vec3_t *origin, vec3_t *direction)
{
	ray->orig = *origin;
	ray->dir = *direction;
}

void ray_get_origin(ray_t *ray, point3_t *orig)
{
	*orig = ray->orig;
}

void ray_get_direction(ray_t *ray, vec3_t *dir)
{
	*dir = ray->dir;
}

void ray_at(ray_t *ray, float t, point3_t *point_result)
{
	vec3_t t_times_dir;
	vec3_scaling(t, &ray->dir, &t_times_dir);

	//p_t = origin + (t * direction)
	vec3_add((vec3_t *)&ray->orig, &t_times_dir, (vec3_t *)point_result);
}

float hit_sphere(point3_t *center, float radius, ray_t *ray)
{
	vec3_t oc;
	vec3_sub(&ray->orig, center, &oc);

	float a = vec3_length_squared(&ray->dir);
	float half_b = vec3_dot_product(&oc, &ray->dir);
	float c = vec3_length_squared(&oc) - (radius * radius);
	float discriminant = (half_b * half_b) - (a * c);

	if(discriminant < 0.0f) {
		return -1.0f;
	} else {
		return (-half_b - sqrt(discriminant)) / a;
	}
}

void set_face_normal(hit_record_t *rec, ray_t *ray, vec3_t *outward_normal)
{
	rec->front_face = vec3_dot_product(&ray->dir, outward_normal) < 0.0f;

	if(rec->front_face == true) {
		rec->normal = *outward_normal;
	} else {
		vec3_t neg_outward_normal;
		vec3_negate(outward_normal, &neg_outward_normal);
		rec->normal = neg_outward_normal;
	}
}

void ray_color(ray_t *ray, color_t *pixel_color, int depth)
{
	hit_record_t rec;

	/* depth count == 0 means there is no much light energy left more */
	if(depth <= 0) {
		color_set(pixel_color, 0.0f, 0.0f, 0.0f);
		return;
	}

	/* recursively refract the light until reaching the max depth */
	if(hittable_list_hit(ray, 0.001, INFINITY, &rec) == true) {
		vec3_t random_vec;
		//vec3_random_in_unit_sphere(&random_vec);
		vec3_random_unit_vector(&random_vec);

		point3_t target;
		vec3_add(&rec.p, &rec.normal, &target);
		vec3_add(&target, &random_vec, &target);

		vec3_t sub_ray_dir;
		vec3_sub(&target, &rec.p, &sub_ray_dir);

		ray_t sub_ray;
		ray_init(&sub_ray, &rec.p, &sub_ray_dir);

		ray_color(&sub_ray, pixel_color, depth-1);

		pixel_color->e[0] *= 0.5;
		pixel_color->e[1] *= 0.5;
		pixel_color->e[2] *= 0.5;

		return;
	}

	vec3_t unit_ray_dir;
	vec3_unit_vector(&ray->dir, &unit_ray_dir);

	/* unit y direction range = -1 ~ 1*/
	float t = 0.5f * (vec3_get_y(&unit_ray_dir) + 1.0f);

	color_t color1, color2;
	color_set(&color1, 1.0f, 1.0f, 1.0f);
	color_set(&color2, 0.5f, 0.7f, 1.0f);

	//color_blended = ((1.0 - t) * color1) + (t * color2)
	color_t tmp1, tmp2;
	color_scaling((1.0 - t), &color1, &tmp1);
	color_scaling(t, &color2, &tmp2);
	color_add(&tmp1, &tmp2, pixel_color);

	return;
}
