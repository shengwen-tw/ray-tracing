#include "vector3.h"
#include "ray.h"

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
