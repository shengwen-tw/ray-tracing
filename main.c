#include <stdio.h>
#include "vector3.h"
#include "color.h"
#include "ray_tracing.h"
#include "rt_objects.h"
#include "camera.h"
#include "common.h"

int main(void)
{
	/* image */
	float aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = (int)((float)(image_width) / aspect_ratio);
	int anti_aliasing_samples = 100;
	int max_depth = 50;

	/* world */
	struct rt_obj rt_obj1;
	rt_object_set_sphere_shape(&rt_obj1, 0.0f, -100.5f, -1.0f, 100.0f);
	rt_object_set_difuse_material(&rt_obj1, 0.8f, 0.8f, 0.0f);

	struct rt_obj rt_obj2;
	rt_object_set_sphere_shape(&rt_obj2, 0.0f, 0.0f, -1.0f, 0.5f);
	rt_object_set_difuse_material(&rt_obj2, 0.7f, 0.3f, 0.3f);

	struct rt_obj rt_obj3;
	rt_object_set_sphere_shape(&rt_obj3, -1.0f, 0.0f, -1.0f, 0.5f);
	rt_object_set_metal_material(&rt_obj3, 0.8f, 0.8f, 0.8f, 0.3f);

	struct rt_obj rt_obj4;
	rt_object_set_sphere_shape(&rt_obj4, 1.0f, 0.0f, -1.0f, 0.5f);
	rt_object_set_metal_material(&rt_obj4, 0.8f, 0.6f, 0.2f, 1.0f);

	rt_object_list_add(&rt_obj1);
	rt_object_list_add(&rt_obj2);
	rt_object_list_add(&rt_obj3);
	rt_object_list_add(&rt_obj4);

	/* camera */
	camera_t camera;
	camera_init(&camera);

	printf("P3\n%d %d\n255\n", image_width, image_height);

	/* plot */
	int i, j, k;
	//row
	for(j = image_height - 1; j >= 0; j--) {
		fprintf(stderr, "\rscanlines remaining: %d\n", j);

		//column
		for(i = 0; i < image_width; i++) {
			color_t pixel_color;
			color_set(&pixel_color, 0.0f, 0.0f, 0.0f);

			/* anti-aliasing */
			for(k = 0; k < anti_aliasing_samples; k++) {
				ray_t ray;
				float u = (float)(i + random_float()) / (image_width - 1.0f);
				float v = (float)(j + random_float()) / (image_height - 1.0f); 
				camera_get_ray(&camera, &ray, u, v);

				color_t sample_color;
				ray_color(&ray, &sample_color, max_depth);
				vec3_add(&pixel_color, &sample_color, &pixel_color);
			}

			write_color(stdout, &pixel_color, anti_aliasing_samples);
		}
	}

	fprintf(stderr, "done.\n");

	return 0;
}
