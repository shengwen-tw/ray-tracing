EXECUTABLE=ray_tracing

CFLAGS=-O2
CFLAGS+=-I./

SRC=main.c \
	vector3.c \
	color.c \
	ray_tracing.c \
	rt_objects.c \
	camera.c \
	common.c \

LDFLAGS=-lm

TEXTURES=./textures/earthmap.jpg
TEXTURES_PPM=$(TEXTURES:.jpg=.ppm)

all: $(TEXTURES_PPM) $(EXECUTABLE)

#convert image to ppm format
$(TEXTURES_PPM): $(TEXTURES)
	@echo "convet texture image" $^ "to" $@
	@convert $^ $@

#compile the ray tracing program
$(EXECUTABLE): $(SRC)
	gcc $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./ray_tracing > output.ppm

show:
	eog output.ppm

png:
	convert output.ppm output.png

clean:
	rm -rf $(EXECUTABLE)
	rm -rf output.ppm
	rm -rf output.png
	rm -rf $(TEXTURES_PPM)

.PHONY: all show clean png
