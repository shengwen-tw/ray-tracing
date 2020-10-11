#include <stdio.h>
#include <stdint.h>
#include "vector3.h"
#include "color.h"
#include "rt_objects.h"
#include "ray_tracing.h"
#include "camera.h"
#include "common.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(void)
{
	int width, height, bpp;
	uint8_t* rgb_image = stbi_load("./textures/earthmap.jpg", &width, &height, &bpp, 3);
	fprintf(stderr, "texture image (%dx%d): \"./textures/earthmap.jpg\" is loaded\n", width, height);

	/* image */
	float aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = (int)((float)(image_width) / aspect_ratio);
	int anti_aliasing_samples = 100;
	int max_depth = 50;

	/* world */
	//rt_set_background_light_color(0.0f, 0.0f, 0.0f);

	struct rt_obj rt_obj1;
	rt_object_set_sphere_shape(&rt_obj1, 0.0f, -100.5f, -1.0f, 100.0f);
	rt_object_set_difuse_material(&rt_obj1, 0.8f, 0.8f, 0.0f);

	struct rt_obj rt_obj2;
	rt_object_set_sphere_shape(&rt_obj2, 0.0f, 0.0f, -1.0f, 0.5f);
	rt_object_set_difuse_material(&rt_obj2, 0.1f, 0.2f, 0.5f);

	struct rt_obj rt_obj3;
	rt_object_set_sphere_shape(&rt_obj3, -1.0f, 0.0f, -1.0f, -0.5f);
	rt_object_set_glass_material(&rt_obj3, 1.5f);

	struct rt_obj rt_obj4;
	rt_object_set_sphere_shape(&rt_obj4, 1.0f, 0.0f, -1.0f, 0.5f);
	rt_object_set_metal_material(&rt_obj4, 0.8f, 0.6f, 0.2f, 0.0f);

	struct rt_obj rt_obj5;
	rt_object_set_rectangle_shape(&rt_obj5, RECTANGLE_XY_PLANE,
				      3.0f, -0.5f, 0.0f,
				      5.0f, 1.0f, 0.0f,
				      -1.0f);
	rt_object_set_difuse_material(&rt_obj5, 0.8f, 0.8f, 0.0f);
	rt_object_set_light_emmision(&rt_obj5, true, 0.5, 0.5, 0.5);

	rt_object_list_add(&rt_obj1);
	rt_object_list_add(&rt_obj2);
	rt_object_list_add(&rt_obj3);
	rt_object_list_add(&rt_obj4);
	rt_object_list_add(&rt_obj5);

	/* camera */
	camera_t camera;

	point3_t look_from;
	vec3_set(&look_from, -2.0f, 2.0f, 1.0f);
//	vec3_set(&look_from, 26.0f, 3.0f, 6.0f);

	point3_t look_at;
	vec3_set(&look_at, 0.0f, 0.0f, -1.0f);
//	vec3_set(&look_at, 0.0f, 2.0f, 0.0f);

	vec3_t vup;
	vec3_set(&vup, 0.0f, 1.0f, 0.0f);

	//camera_set_default(&camera);
	camera_set(&camera, &look_from, &look_at, &vup, 60, aspect_ratio);

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
				ray_color(&ray, &sample_color, u, v, max_depth);
				vec3_add(&pixel_color, &sample_color, &pixel_color);
			}

			write_color(stdout, &pixel_color, anti_aliasing_samples);
		}
	}

	fprintf(stderr, "done.\n");

	return 0;
}
