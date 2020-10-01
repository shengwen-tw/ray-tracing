#include <stdio.h>
#include "vector3.h"
#include "color.h"

int main(void)
{
	int image_width = 256;
	int image_height = 256;

	printf("P3\n%d %d\n255\n", image_width, image_height);

	int i, j;
	//row
	for(j = image_height - 1; j >= 0; j--) {
		fprintf(stderr, "\rscan lines remaining: %d\n", j);

		//column
		for(i = 0; i < image_width; i++) {
			/* rgb intensity (0.0~1.0) */
			float r = (float)i / (float)(image_width - 1);
			float g = (float)j / (float)(image_height - 1);
			float b = 0.25f;

			color_t pixel_color;
			color_set(&pixel_color, r, g, b);

			write_color(stdout, &pixel_color);
		}
	}

	fprintf(stderr, "done.\n");

	return 0;
}
