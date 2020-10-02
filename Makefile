SRC=main.c \
	vector3.c \
	color.c \
	ray.c \
	sphere.c \
	hittable_objects.c \
	camera.c \
	common.c

CFLAGS=-I./

LDFLAGS=-lm

all:
	gcc $(CFLAGS) -o ray_tracing $(SRC) $(LDFLAGS)
	./ray_tracing > output.ppm

show:
	eog output.ppm

clean:
	rm ray_tracing
	rm output.ppm

.PHONY: all show clean
