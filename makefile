all: raytracer

raytracer: obj
	g++ -std=c++11 -o RayTracer -O3 main.o camera.o hittable_list.o materials.o ray.o sphere.o vec3.o
	rm -rf *.o

obj:
	g++ -std=c++11 -c main.cpp camera.cpp hittable_list.cpp materials.cpp ray.cpp sphere.cpp vec3.cpp

clean:
	rm -rf *.o
	rm -rf ./RayTracer
