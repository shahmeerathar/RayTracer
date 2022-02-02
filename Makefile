BUILDDIR = build
SRCDIR = src
OUTDIR = bin
LIBDIR = lib
OUT = $(OUTDIR)/RayTracer

_SRCS = main.cpp Camera.cpp HittableList.cpp Materials.cpp Ray.cpp Sphere.cpp Vec3.cpp CPURenderer.cpp GPURenderer.cpp
SRCS = $(patsubst %,$(SRCDIR)/%,$(_SRCS))
_OBJS = main.o Camera.o HittableList.o Materials.o Ray.o Sphere.o Vec3.o CPURenderer.o GPURenderer.o
OBJS = $(patsubst %,$(BUILDDIR)/%,$(_OBJS))

SHADER = GPURayTracer
SHADERSRC = $(patsubst %,$(SRCDIR)/%,$(SHADER)).metal
SHADERLIB = $(patsubst %,$(LIBDIR)/%,$(SHADER)).metallib

METALPATH = lib/metal-cpp
LIBS = -framework Foundation -framework Metal -framework QuartzCore
CC = g++
CFLAGS = -std=c++20 -O3 -I$(METALPATH) $(LIBS)
rmO = rm -rf $(BUILDDIR)/*.o

all: $(BUILDDIR) $(OUTDIR) $(LIBDIR) raytracer

metal:
	xcrun -sdk macosx metal -c $(SHADERSRC) -o $(BUILDDIR)/$(SHADER).air
	xcrun -sdk macosx metallib $(BUILDDIR)/$(SHADER).air -o $(SHADERLIB)

$(BUILDDIR):
	mkdir $@

$(OUTDIR):
	mkdir $@

$(LIBDIR):
	mkdir $@

raytracer: metal $(OBJS)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)
	rm -rf $(OUTDIR)
	rm -rf renders/image.ppm
	rm -rf $(LIBDIR)/*.metallib
