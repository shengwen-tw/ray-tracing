#include <stdbool.h>
#include "vector3.h"
#include "rt_objects.h"
#include "ray_tracing.h"

struct rt_obj *object_list_start;

/*---------------*
 * shape setting *
 *---------------*/
void rt_object_set_sphere_shape(struct rt_obj *obj,
	float center_x, float center_y, float center_z, float radius)
{
	obj->hittable_type = RT_SHAPE_SPHERE;
	obj->sphere.center.e[0] = center_x ;
	obj->sphere.center.e[1] = center_y;
	obj->sphere.center.e[2] = center_z;
	obj->sphere.radius = radius;
	obj->next = NULL;
}

void rt_object_set_rectangle_shape(struct rt_obj *obj,
        float x0, float y0, float x1, float y1, float k)
{
	obj->hittable_type = RT_SHAPE_RECTANGLE;
	obj->rectangle.x0 = x0;
	obj->rectangle.y0 = y0;
	obj->rectangle.x1 = x1;
	obj->rectangle.y1 = y1;
	obj->rectangle.k = k;
	obj->next = NULL;
}

/*------------------*
 * material setting *
 *------------------*/
void rt_object_set_difuse_material(struct rt_obj *obj,
	float albedo_red, float albedo_green, float albedo_blue)
{
	obj->material = LAMBERTIAN;
	obj->albedo.e[0] = albedo_red;
	obj->albedo.e[1] = albedo_green;
	obj->albedo.e[2] = albedo_blue;
}

void rt_object_set_metal_material(struct rt_obj *obj,
	float albedo_red, float albedo_green, float albedo_blue, float fuzzyness)
{
	obj->material = METAL;
	obj->albedo.e[0] = albedo_red;
	obj->albedo.e[1] = albedo_green;
	obj->albedo.e[2] = albedo_blue;
	obj->metal_fuzzyness = fuzzyness;
}

void rt_object_set_glass_material(struct rt_obj *obj, float index_of_refraction)
{
	obj->material = GLASS;
	obj->albedo.e[0] = 1.0f;
	obj->albedo.e[1] = 1.0f;
	obj->albedo.e[2] = 1.0f;
	obj->glass_ir = index_of_refraction;
}

/*-------------*
 * object list *
 *-------------*/
void hittable_list_clear(void)
{
	object_list_start = NULL;
}

void rt_object_list_add(struct rt_obj *new_obj)
{
	/* list is clear, push first element */
	if(object_list_start == NULL) {
		//fprintf(stderr, "add first hittalbe object.\n");
		object_list_start = new_obj;
		return;
	}

	struct rt_obj *list_ptr = object_list_start;

	while(1) {
		if(list_ptr->next == NULL) {
			//fprintf(stderr, "add new hittalbe object.\n");
			list_ptr->next = new_obj;
			break;
		} else {
			list_ptr = list_ptr->next;
		}
	}
}

bool rt_object_list_hit(ray_t *ray, float t_min, float t_max, hit_record_t *rec,
                       struct rt_obj **hit_obj)
{
	if(object_list_start == NULL) return false;

	hit_record_t tmp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;

	struct rt_obj *list_ptr = object_list_start;
	bool hit_test = false;
	while(1) {
		switch(list_ptr->hittable_type) {
		case RT_SHAPE_SPHERE:
			hit_test = sphere_hit(&list_ptr->sphere, ray, t_min,
					      closest_so_far, &tmp_rec);
			break;
		case RT_SHAPE_RECTANGLE:
			hit_test = rectangle_hit(&list_ptr->rectangle, ray, t_min,
						 closest_so_far, &tmp_rec);
			break;
		default:
			break;
		}

		if(hit_test == true) {
			*hit_obj = list_ptr;
			hit_anything = true;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}

		if(list_ptr->next == NULL) {
			break;
		} else {
			list_ptr = list_ptr->next;
		}
	}

	return hit_anything;
}
