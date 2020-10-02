#ifndef __COLOR_H__
#define __COLOR_H__

#include <stdio.h>
#include "vector3.h"

#define color_set(color, r, g, b) vec3_set((vec3_t *)color, r, g, b)
#define color_get_r vec3_get_x
#define color_get_g vec3_get_y
#define color_get_b vec3_get_z
#define color_add(color1, color2, color_result) \
	vec3_add((vec3_t *)color1, (vec3_t *)color2, (vec3_t *)color_result)
#define color_scaling(factor, color, color_result) \
	vec3_scaling(factor, (vec3_t *)color, (vec3_t *)color_result)

typedef vec3_t color_t;

void write_color(FILE *stream, color_t *color, int anti_aliasing_samples);

#endif
