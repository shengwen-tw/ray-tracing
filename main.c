#include <stdio.h>
#include "vector3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_objects.h"
#include "camera.h"

int main(void)
{
	/* image */
	float aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = (int)((float)(image_width) / aspect_ratio);

	/* world */
	sphere_t ball1, ball2;
	point3_t ball1_orig, ball2_orig;
	point3_set(&ball1_orig, 0, 0, -1);
	point3_set(&ball2_orig, 0, -100.5, -1);
	sphere_init(&ball1, &ball1_orig, 0.5f);
	sphere_init(&ball2, &ball2_orig, 100.0f);

	struct hittable_obj hittable_obj1, hittable_obj2; 
	hittalbe_object_sphere_init(&hittable_obj1, &ball1);
	hittalbe_object_sphere_init(&hittable_obj2, &ball2);
	hittable_list_add(&hittable_obj2);
	hittable_list_add(&hittable_obj1);

	/* camera */
	camera_t camera;
	camera_init(&camera);

	printf("P3\n%d %d\n255\n", image_width, image_height);

	/* plot */
	int i, j;
	//row
	for(j = image_height - 1; j >= 0; j--) {
		fprintf(stderr, "\rscan lines remaining: %d\n", j);

		//column
		for(i = 0; i < image_width; i++) {
			float u = (float)i / (float)(image_width - 1);
			float v = (float)j / (float)(image_height - 1); 

			ray_t ray;
			camera_get_ray(&camera, &ray, u, v);

			color_t pixel_color;
			ray_color(&ray, &pixel_color);

			write_color(stdout, &pixel_color);
		}
	}

	fprintf(stderr, "done.\n");

	return 0;
}
