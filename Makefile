OBJDIR = obj
SRCDIR = src
OUTDIR = bin
OUT = $(OUTDIR)/RayTracer

_SRCS = main.cpp camera.cpp hittable_list.cpp materials.cpp ray.cpp sphere.cpp vec3.cpp
SRCS = $(patsubst %,$(SRCDIR)/%,$(_SRCS))
_OBJS = main.o camera.o hittable_list.o materials.o ray.o sphere.o vec3.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

METALPATH = lib/metal-cpp
LIBS = -framework Foundation -framework Metal -framework QuartzCore
CC = g++
CFLAGS = -std=c++20 -O3 -Iinclude -I$(METALPATH) $(LIBS)
rmO = rm -rf $(OBJDIR)/*.o

all: $(OBJDIR) $(OUTDIR) raytracer

$(OBJDIR):
	mkdir $@

$(OUTDIR):
	mkdir $@

raytracer: $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf obj
	rm -rf bin
	rm -rf renders/image.ppm
