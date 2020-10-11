EXECUTABLE=ray_tracing

CFLAGS=-O2
CFLAGS+=-I./
CFLAGS+=-I./lib/stb

SRC=main.c \
	vector3.c \
	color.c \
	ray_tracing.c \
	rt_objects.c \
	camera.c \
	common.c \

LDFLAGS=-lm

#convert image to ppm format
$(TEXTURES_PPM): $(TEXTURES)
	@echo "convet texture image" $^ "to" $@
	@convert $^ -compress none $@

#compile the ray tracing program
$(EXECUTABLE): $(SRC)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@./$(EXECUTABLE) > output.ppm

run:
	@./$(EXECUTABLE) > output.ppm

show:
	eog output.ppm

png:
	convert output.ppm output.png

clean:
	rm -rf $(EXECUTABLE)
	rm -rf output.ppm
	rm -rf output.png

.PHONY: run show clean png
