#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "ray_tracing.h"
#include "color.h"
#include "rt_objects.h"
#include "common.h"

int background_light_mode;
color_t background_light_color;

//initialize ray's origin and directional vector
void ray_init(ray_t *ray, vec3_t *origin, vec3_t *direction)
{
	ray->orig = *origin;
	ray->dir = *direction;
}

//calculate a point on a ray
void ray_at(ray_t *ray, float t, point3_t *point_result)
{
	vec3_t t_times_dir;
	vec3_scaling(t, &ray->dir, &t_times_dir);

	//p_t = origin + (t * direction)
	vec3_add((vec3_t *)&ray->orig, &t_times_dir, (vec3_t *)point_result);
}

//set normal vector of a shape
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

float reflectance_shicks_method(float consine, float ref_index)
{
	float r0 = (1.0f - ref_index) / (1.0f + ref_index);
	r0 = r0 * r0;
	return r0 + ((1.0f - r0) * pow(1.0f - consine, 5.0f));
}

/*--------------------------*
 * ray - shape intersection *
 *--------------------------*/
bool sphere_hit(sphere_t *sphere, ray_t *ray, float t_min, float t_max, hit_record_t *rec)
{
        vec3_t oc;
        vec3_sub(&ray->orig, &sphere->center, &oc);

        float a = vec3_length_squared(&ray->dir);
        float half_b = vec3_dot_product(&oc, &ray->dir);
        float c = vec3_length_squared(&oc) - (sphere->radius * sphere->radius);
        float discriminant = (half_b * half_b) - (a * c);

	if(discriminant > 0.0f) {
		float root = sqrt(discriminant);

		float tmp = (-half_b - root) / a;
		if(tmp < t_max && tmp > t_min) {
			rec->t = tmp;
			ray_at(ray, rec->t, &rec->p);

			vec3_t vec_tmp;
			vec3_sub(&rec->p, &sphere->center, &vec_tmp);
			vec3_div(sphere->radius, &vec_tmp, &rec->normal);

			vec3_t outward_normal;
			vec3_sub(&rec->p, &sphere->center, &vec_tmp);
			vec3_div(sphere->radius, &vec_tmp, &outward_normal);
			set_face_normal(rec, ray, &outward_normal);

			return true;
		}

		tmp = (-half_b + root) / a;
		if(tmp < t_max && tmp > t_min) {
			rec->t = tmp;
			ray_at(ray, rec->t, &rec->p);

			vec3_t vec_tmp;
			vec3_sub(&rec->p, &sphere->center, &vec_tmp);
			vec3_div(sphere->radius, &vec_tmp, &rec->normal);

			vec3_t outward_normal;
			vec3_sub(&rec->p, &sphere->center, &vec_tmp);
			vec3_div(sphere->radius, &vec_tmp, &outward_normal);
			set_face_normal(rec, ray, &outward_normal);

			return true;
		}
	}

	return false;
}

bool rectangle_hit(rectangle_t *rectangle, ray_t *ray, float t0, float t1,
		   hit_record_t *rec)
{
	float t;
	float ray_x, ray_y, ray_z;
	vec3_t outward_normal;

	switch(rectangle->plane) {
	case RECTANGLE_XY_PLANE:
		t = (rectangle->k - vec3_get_z(&ray->orig)) / vec3_get_z(&ray->dir);

		ray_x = vec3_get_x(&ray->orig) + vec3_get_x(&ray->dir) * t;
		ray_y = vec3_get_y(&ray->orig) + vec3_get_y(&ray->dir) * t;

		if(ray_x < rectangle->x0 || ray_x > rectangle->x1 ||
		   ray_y < rectangle->y0 || ray_y > rectangle->y1) {
			return false;
		}

		rec->u = (ray_x - rectangle->x0) / (rectangle->x1 - rectangle->x0);
		rec->v = (ray_y - rectangle->y0) / (rectangle->y1 - rectangle->y0);
		rec->t = t;

		vec3_set(&outward_normal, 0.0f, 0.0f, 1.0f);

		break;
	case RECTANGLE_XZ_PLANE:
		t = (rectangle->k - vec3_get_y(&ray->orig)) / vec3_get_y(&ray->dir);

		ray_x = vec3_get_x(&ray->orig) + vec3_get_x(&ray->dir) * t;
		ray_z = vec3_get_y(&ray->orig) + vec3_get_z(&ray->dir) * t;

		if(ray_x < rectangle->x0 || ray_x > rectangle->x1 ||
		   ray_z < rectangle->z0 || ray_z > rectangle->z1) {
			return false;
		}

		rec->u = (ray_x - rectangle->x0) / (rectangle->x1 - rectangle->x0);
		rec->v = (ray_z - rectangle->z0) / (rectangle->z1 - rectangle->z0);
		rec->t = t;

		vec3_set(&outward_normal, 0.0f, 1.0f, 0.0f);

		break;
	case RECTANGLE_YZ_PLANE:
		t = (rectangle->k - vec3_get_x(&ray->orig)) / vec3_get_x(&ray->dir);

		ray_y = vec3_get_y(&ray->orig) + vec3_get_y(&ray->dir) * t;
		ray_z = vec3_get_z(&ray->orig) + vec3_get_z(&ray->dir) * t;

		if(ray_y < rectangle->y0 || ray_y > rectangle->y1 ||
		   ray_z < rectangle->z0 || ray_z > rectangle->z1) {
			return false;
		}

		rec->u = (ray_y - rectangle->y0) / (rectangle->y1 - rectangle->y0);
		rec->v = (ray_z - rectangle->z0) / (rectangle->z1 - rectangle->z0);
		rec->t = t;

		vec3_set(&outward_normal, 1.0f, 0.0f, 0.0f);

		break;
	}

	ray_at(ray, t, &rec->p);

	return true;
}

/*-------------------*
 * material handling *
 *-------------------*/
bool lambertian_scattering(ray_t *ray_in, hit_record_t *rec, ray_t *scattered_ray)
{
	vec3_t random_vec;
	//vec3_random_in_unit_sphere(&random_vec);
	//vec3_random_unit_vector(&random_vec);
	vec3_random_in_hemisphere(&random_vec, &rec->normal);

	point3_t target;
	vec3_add(&rec->p, &rec->normal, &target);
	vec3_add(&target, &random_vec, &target);

	vec3_t scattered_ray_dir;
	vec3_sub(&target, &rec->p, &scattered_ray_dir);

	ray_init(scattered_ray, &rec->p, &scattered_ray_dir);

	return true;
}

bool metal_scattering(ray_t *ray_in, hit_record_t *rec, ray_t *scattered_ray, float fuzzyness)
{
	/* create reflection */	
	vec3_t r_in_dir_unit;
	vec3_unit_vector(&ray_in->dir, &r_in_dir_unit);

	vec3_t reflected_vec;
	vec3_reflect(&r_in_dir_unit, &rec->normal, &reflected_vec);

	/* create fuzzyness */
	vec3_t random_vec, fuzzy_random_vec;
	vec3_random_unit_vector(&random_vec);
	vec3_scaling(fuzzyness, &random_vec, &fuzzy_random_vec);

	/* scattered ray vector = reflection vector + fuzzy random vector */
	vec3_t fuzzy_reflected_vec;
	vec3_add(&reflected_vec, &fuzzy_random_vec, &fuzzy_reflected_vec);
	ray_init(scattered_ray, &rec->p, &fuzzy_reflected_vec);

	return (vec3_dot_product(&reflected_vec, &rec->normal) > 0.0f);
}

bool glass_scattering(ray_t *ray_in, hit_record_t *rec, ray_t *scattered_ray, float ir)
{
	float refraction_ratio = rec->front_face ? (1.0f / ir) : ir;
	
	vec3_t unit_dir;
	vec3_unit_vector(&ray_in->dir, &unit_dir);

	vec3_t neg_unit_dir;
	vec3_negate(&unit_dir, &neg_unit_dir);

	float cos_theta = fmin(vec3_dot_product(&neg_unit_dir, &rec->normal), 1.0f);
	float sin_theta = sqrt(1.0f - cos_theta*cos_theta);
	
	bool cannot_refract = refraction_ratio * sin_theta > 1.0f;

	vec3_t direction;
	if(cannot_refract == true ||
	   reflectance_shicks_method(cos_theta, refraction_ratio) > random_float()) {
		vec3_reflect(&unit_dir, &rec->normal, &direction);
	} else {
		vec3_refract(&unit_dir, &rec->normal, refraction_ratio, &direction);
	}
	
	vec3_refract(&unit_dir, &rec->normal, refraction_ratio, &direction);

	ray_init(scattered_ray, &rec->p, &direction);

	return true;
}

void pixel_color_from_image(uint8_t *image, int width, int height,
			    float u, float v, color_t *pixel_color)
{
	const int rgb_channel_bytes = 3;

	u = clamp(u, 0.0, 1.0);
	v = 1.0 - clamp(v, 0.0, 1.0);

	int i = u * width;
	int j = v * height;

	if (i >= width)  i = width - 1;
	if (j >= height) j = height - 1;

	int r_index = (j * width * rgb_channel_bytes) + (i * rgb_channel_bytes) + 0;
	int g_index = (j * width * rgb_channel_bytes) + (i * rgb_channel_bytes) + 1;
	int b_index = (j * width * rgb_channel_bytes) + (i * rgb_channel_bytes) + 2;

	float div_255 = 1.0f / 255.0f;
	pixel_color->e[0] = image[r_index] * div_255;
	pixel_color->e[1] = image[g_index] * div_255;
	pixel_color->e[2] = image[b_index] * div_255;
}

/*-------------*
 * ray tracing *
 *-------------*/
void rt_set_background_light_color(float r, float g, float b)
{
	background_light_color.e[0] = r;
	background_light_color.e[1] = g;
	background_light_color.e[2] = b;
	background_light_mode = BACKGROUND_LIGHT_USE_DEFAULT;
}

void rt_set_use_default_background_light(void)
{
	background_light_mode = BACKGROUND_LIGHT_USE_ASSIGNED_COLOR;
}

void emit_default_background_light(ray_t *ray, color_t *pixel_color)
{
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

void ray_color(ray_t *ray, color_t *pixel_color, float u, float v, int depth)
{
	hit_record_t rec;
	int hit_material;
	struct rt_obj *hit_obj;

	/* depth count == 0 means there is no much light energy left more */
	if(depth <= 0) {
		color_set(pixel_color, 0.0f, 0.0f, 0.0f);
		return;
	}

	bool valid_scattering = false;
	/* recursively refract the light until reaching the max depth */
	if(rt_object_list_hit(ray, 0.001, INFINITY, &rec, &hit_obj) == true) {
		ray_t sub_ray;

		switch(hit_obj->material) {
		case LAMBERTIAN:
			valid_scattering = lambertian_scattering(ray, &rec, &sub_ray);
			break;
		case METAL:
			valid_scattering = metal_scattering(ray, &rec, &sub_ray,
                                                            hit_obj->metal_fuzzyness);
			break;
		case GLASS:
			valid_scattering = glass_scattering(ray, &rec, &sub_ray,
                                                            hit_obj->glass_ir);
			break;
		default:
			break;
		}

		if(valid_scattering == true) {
			ray_color(&sub_ray, pixel_color, u, v, depth-1);

			/* apply attenuation (albedo) of color after every scattering */
			pixel_color->e[0] *= hit_obj->albedo.e[0];
			pixel_color->e[1] *= hit_obj->albedo.e[1];
			pixel_color->e[2] *= hit_obj->albedo.e[2];

			if(hit_obj->emit_light == true) {
				pixel_color->e[0] += hit_obj->emit_light_color.e[0];
				pixel_color->e[1] += hit_obj->emit_light_color.e[1];
				pixel_color->e[2] += hit_obj->emit_light_color.e[2];
			}

			return;
		}
	} 

	/* if ray didn't hit any thing, than camera catch the background light */
	switch(background_light_mode) {
	case BACKGROUND_LIGHT_USE_DEFAULT:
		emit_default_background_light(ray, pixel_color);
		break;
	case BACKGROUND_LIGHT_USE_ASSIGNED_COLOR:
		*pixel_color = background_light_color;
		break;
	}

	return;
}
