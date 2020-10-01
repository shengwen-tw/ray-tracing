#include <stdio.h>
#include "color.h"

void write_color(FILE *stream, color_t *color)
{
	int ir = 255.9f * color_get_r(color);
	int ig = 255.9f * color_get_g(color);
	int ib = 255.9f * color_get_b(color);

	fprintf(stream, "%d %d %d\n", ir, ig, ib);
}
