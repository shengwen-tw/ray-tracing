#include <stdio.h>
#include "color.h"
#include "common.h"

void write_color(FILE *stream, color_t *color, int anti_aliasing_samples)
{
	float r = color_get_r(color);
	float g = color_get_g(color);
	float b = color_get_b(color);

	/* divide by sample number first then do gamma-correcton for gamma = 2 */
	float scale = 1.0f / anti_aliasing_samples;
	r = sqrt(r * scale);
	g = sqrt(g * scale);
	b = sqrt(b * scale);

	int ir = 256.0f * clamp(r, 0.0f, 0.999f);
	int ig = 256.0f * clamp(g, 0.0f, 0.999f);
	int ib = 256.0f * clamp(b, 0.0f, 0.999f);

	fprintf(stream, "%d %d %d\n", ir, ig, ib);
}
