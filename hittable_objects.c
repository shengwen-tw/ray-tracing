#include "sphere.h"
#include "hittable_objects.h"

struct hittable_obj *object_list_start;

void hittalbe_object_sphere_init(struct hittable_obj *new_obj,
	float center_x, float center_y, float center_z, float radius, int material)
{
	new_obj->hittable_type = HITTALBE_TYPE_SPHERE;
	new_obj->sphere.center.e[0] = center_x ;
	new_obj->sphere.center.e[1] = center_y;
	new_obj->sphere.center.e[2] = center_z;
	new_obj->sphere.radius = radius;
	new_obj->material = material;
	new_obj->next = NULL;
}

void hittable_list_clear(void)
{
	object_list_start = NULL;
}

void hittable_list_add(struct hittable_obj *new_obj)
{
	/* list is clear, push first element */
	if(object_list_start == NULL) {
		//fprintf(stderr, "add first hittalbe object.\n");
		object_list_start = new_obj;
		return;
	}

	struct hittable_obj *list_ptr = object_list_start;

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

bool hittable_list_hit(ray_t *ray, float t_min, float t_max, hit_record_t *rec)
{
	if(object_list_start == NULL) return false;

	hit_record_t tmp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;

	struct hittable_obj *list_ptr = object_list_start;
	bool hit_test = false;
	while(1) {
		switch(list_ptr->hittable_type) {
		case HITTALBE_TYPE_SPHERE:
			hit_test = sphere_hit(&list_ptr->sphere, ray, t_min, closest_so_far, &tmp_rec);
			break;
		default:
			break;
		}

		if(hit_test == true) {
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
