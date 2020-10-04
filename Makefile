SRC=main.c \
	vector3.c \
	color.c \
	ray.c \
	sphere.c \
	rt_objects.c \
	camera.c \
	common.c \

CFLAGS=-I./

LDFLAGS=-lm

all:
	gcc $(CFLAGS) -o ray_tracing $(SRC) $(LDFLAGS)
	./ray_tracing > output.ppm

show:
	eog output.ppm

png:
	convert output.ppm output.png

clean:
	rm ray_tracing
	rm output.ppm
	rm output.png

.PHONY: all show clean png
