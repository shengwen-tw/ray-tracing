#include <stdio.h>
#include "vector3.h"
#include "color.h"
#include "ray.h"

int main(void)
{
	/* image */
	float aspect_ratio = 16.0 / 9.0;
	int image_width = 400;
	int image_height = (int)((float)(image_width) / aspect_ratio);

	/* camera */
	float viewport_height = 2.0f;
	float viewport_width = aspect_ratio * viewport_height;

	float focal_length = 1.0f;
	vec3_t vec_focal_length;
	vec3_set(&vec_focal_length, 0.0f, 0.0f, focal_length);

	vec3_t origin;
	vec3_set(&origin, 0.0f, 0.0f, 0.0f);

	vec3_t horizontal, half_horizontal;
	vec3_set(&horizontal, viewport_width, 0.0f, 0.0f);
	vec3_scaling(0.5f, &horizontal, &half_horizontal);

	vec3_t vertical, half_vertical;
	vec3_set(&vertical, 0.0f, viewport_height, 0.0f);
	vec3_scaling(0.5f, &vertical, &half_vertical);

	//lower_left_corner = origin - horizontal/2 - vertical/2 - (0, 0, focal_length)
	vec3_t lower_left_corner, tmp1, tmp2;
	vec3_sub(&origin, &half_horizontal, &tmp1);
	vec3_sub(&tmp1, &half_vertical, &tmp2);
	vec3_sub(&tmp2, &vec_focal_length, &lower_left_corner);

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

			//ray_direction = lower_left_corner + u*horizontal + v*horizontal - origin
			vec3_t ray_direction, u_horizontal, v_vertical, tmp1, tmp2;
			vec3_scaling(u, &horizontal, &u_horizontal);
			vec3_scaling(v, &vertical, &v_vertical);
			vec3_add(&lower_left_corner, &u_horizontal, &tmp1);
			vec3_add(&tmp1, &v_vertical, &tmp2);
			vec3_sub(&tmp2, &origin, &ray_direction);

			ray_t ray;
			ray_init(&ray, &origin, &ray_direction);

			color_t pixel_color;
			ray_color(&ray, &pixel_color);

			write_color(stdout, &pixel_color);
		}
	}

	fprintf(stderr, "done.\n");

	return 0;
}
