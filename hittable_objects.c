#include "sphere.h"
#include "hittable_objects.h"

struct hittable_obj *object_list_start;

void hittalbe_object_sphere_init(struct hittable_obj *new_obj, sphere_t *sphere)
{
	new_obj->hittable_type = HITTALBE_TYPE_SPHERE;
	new_obj->sphere = *sphere;
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
