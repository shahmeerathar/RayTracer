#include "Commons.h"
#include "Camera.h"
#include "Hittable.h"
#include "sphere.h"
#include "HittableList.h"
#include "materials.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <thread>
#include <mutex>
#include <future>

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Metal/Metal.hpp>

using namespace std;


colour colour_ray(const ray& r, const Hittable& object, int depth)
{
	HitRecord record;

    if (depth > 50)
    {
        return {0.0, 0.0, 0.0};
    }

	if (object.hit(r, 0.001, infinity, record))
	{
        ray scattered = r;
        colour attenuation;
        if (record.mtrPtr->scatter(r, record, attenuation, scattered))
        {
            return attenuation * colour_ray(scattered, object, depth + 1);
        }
        return colour(0.0, 0.0, 0.0);
	}

    vec3 unit_direction = unit(r.direction);
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.5, 0.7, 1.0);
}

Camera get_camera(double aspect_ratio)
{
    point3 lookfrom = point3(3,3,2);
    point3 lookat = point3(0,0,-1);
    point3 vup = vec3(0,1,0);
    double fov_angle = 20.0;
    double aperture = 2.0;
    double focus_distance = (lookfrom - lookat).length();
    bool dof = false;
    Camera cam(lookfrom, lookat, vup, fov_angle, aspect_ratio, aperture, focus_distance, dof);

    return cam;
}

HittableList get_scene()
{
    //Defining objects and materials
    shared_ptr<Material> material_1 = make_shared<Lambertian>(colour(0.8, 0.8, 0.0));
    shared_ptr<Material> material_2 = make_shared<Lambertian>(colour(0.7, 0.3, 0.3));
    shared_ptr<Material> material_3 = make_shared<metal>(colour(0.8, 0.8, 0.8), 0.001);
    shared_ptr<Material> material_4 = make_shared<metal>(colour(0.8, 0.6, 0.2), 0.2);
    shared_ptr<Material> material_5 = make_shared<dielectric>(1.5);

    HittableList objects = HittableList();
    objects.add(make_shared<sphere>(point3(0.0, 0.0, -1), 0.5, material_1));
    objects.add(make_shared<sphere>(point3(0.0, -100.5, -1), 100, material_2));
    objects.add(make_shared<sphere>(point3(0.25, 0.25, -0.5), 0.1, material_4));
    objects.add(make_shared<sphere>(point3(-0.25, 0.25, -0.5), 0.1, material_3));
    objects.add(make_shared<sphere>(point3(0.0, 0.3, -0.6), 0.15, material_5));

    HittableList world;

    auto material_ground = make_shared<Lambertian>(colour(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(colour(0.1, 0.2, 0.5));
    auto material_left = make_shared<Lambertian>(colour(0.5, 0.2, 0.3));
    auto material_right  = make_shared<metal>(colour(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0), -0.45, material_left));
    world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

    return world;
}

int main()
{
    //Defining image properties and Camera
    double aspect_ratio = 1.0/1.0;
    int img_width  = 1200;
    int img_height = static_cast<int>(static_cast<double>(img_width) / aspect_ratio);
    int samples_per_pixel = 100;

    Camera cam = get_camera(aspect_ratio);
    HittableList scene = get_scene();

    MTL::Device* device = MTL::CreateSystemDefaultDevice();
    cout << device->name()->utf8String();

    int no_of_threads = std::thread::hardware_concurrency();

    ofstream image ("../renders/image.ppm");
    if (image.is_open())
    {
        int index = 0;
        image << "P3\n" << img_width << ' ' << img_height << "\n255\n";
        for (int i = img_height; i > 0; i--)
        {
            for (int j = 0; j < img_width; j = j + no_of_threads)
            {
                mutex mutex;
                auto render_pixel = [&] (int x)
                {
                    colour pixel = colour(0.0, 0.0, 0.0);
                    for (int s = 0; s < samples_per_pixel; s++)
                    {
                        double u = (static_cast<double>(x) + randomDouble()) / static_cast<double>(img_width);
                        double v = (static_cast<double>(i) + randomDouble()) / static_cast<double>(img_height);
                        ray r = cam.getRay(u, v);
                        pixel += colour_ray(r, scene, 1);
                    }
                    pixel *= (1.0 / static_cast<double>(samples_per_pixel));
                    return pixel;
                };
                auto output_pixel = [&] (colour pixel)
                {
                    int red = static_cast<int>(pixel.x * 255);
                    int green = static_cast<int>(pixel.y * 255);
                    int blue = static_cast<int>(pixel.z * 255);
                    mutex.lock();
                    image << red << ' ' << green << ' ' << blue << '\n';
                    cout << "Rendered: " << (index*100)/(img_width*img_height) << '%' << " - remaining pixels: " << img_width*img_height - 1 - index << '\n';
                    mutex.unlock();
                    index++;
                };

                //Concurrency
                vector<std::future<colour>> futures;
                for(int i = 0; i < no_of_threads; i++)
                {
                    futures.push_back(std::async(render_pixel, j + i));
                }
                for (auto& f : futures)
                {
                    output_pixel(f.get());
                }
            }
        }
        image.close();
    }
    return 0;
}
