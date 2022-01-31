OBJDIR = obj
SRCDIR = src
OUT = bin/RayTracer

_SRCS = main.cpp camera.cpp hittable_list.cpp materials.cpp ray.cpp sphere.cpp vec3.cpp
SRCS = $(patsubst %,$(SRCDIR)/%,$(_SRCS))
_OBJS = main.o camera.o hittable_list.o materials.o ray.o sphere.o vec3.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

CC = g++
CFLAGS = -std=c++20 -O3 -Iinclude
rmO = rm -rf $(OBJDIR)/*.o

all: raytracer

raytracer: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(rmO)
	rm -rf bin/RayTracer
	rm -rf renders/image.ppm
