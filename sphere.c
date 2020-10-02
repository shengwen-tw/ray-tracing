#include <stdbool.h>
#include <math.h>
#include "vector3.h"
#include "ray.h"
#include "sphere.h"

void sphere_init(sphere_t *sphere, point3_t *center, float r)
{
	sphere->center = *center;
	sphere->radius = r;
}

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

			return true;
		}

		tmp = (-half_b + root) / a;
		if(tmp < t_max && tmp > t_min) {
			rec->t = tmp;
			ray_at(ray, rec->t, &rec->p);

			vec3_t vec_tmp;
			vec3_sub(&rec->p, &sphere->center, &vec_tmp);
			vec3_div(sphere->radius, &vec_tmp, &rec->normal);

			return true;
		}
	}
}
