OBJDIR = obj
SRCDIR = src
OUTDIR = bin
OUT = $(OUTDIR)/RayTracer

_SRCS = main.cpp Camera.cpp HittableList.cpp Materials.cpp Ray.cpp Sphere.cpp Vec3.cpp Renderer.cpp CPURenderer.cpp GPURenderer.cpp
SRCS = $(patsubst %,$(SRCDIR)/%,$(_SRCS))
_OBJS = main.o Camera.o HittableList.o Materials.o Ray.o Sphere.o Vec3.o Renderer.o CPURenderer.o GPURenderer.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

METALPATH = lib/metal-cpp
LIBS = -framework Foundation -framework Metal -framework QuartzCore
CC = g++
CFLAGS = -std=c++20 -O3 -I$(METALPATH) $(LIBS)
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
