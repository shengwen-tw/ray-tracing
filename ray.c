#include <stdbool.h>
#include "ray.h"
#include "color.h"

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

bool hit_sphere(point3_t *center, float radius, ray_t *ray)
{
	vec3_t oc;
	vec3_sub(&ray->orig, center, &oc);

	float a = vec3_dot_product(&ray->dir, &ray->dir);
	float b = 2.0f * vec3_dot_product(&oc, &ray->dir);
	float c = vec3_dot_product(&oc, &oc) - (radius * radius);

	float discriminant = b*b - 4.0f*a*c;

	return (discriminant > 0.0f);
}

void ray_color(ray_t *ray, color_t *pixel_color)
{
	/* create a sphere */
	point3_t sphere_center;
	point3_set(&sphere_center, 0.0f, 0.0f, -1.0f);

	if(hit_sphere(&sphere_center, 0.5, ray) == true) {
		color_set(pixel_color, 1.0f, 0.0f, 0.0f);
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
}
