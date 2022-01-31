#include "Commons.h"
#include "Camera.h"
#include "Hittable.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Materials.h"

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

Colour colourRay(const Ray &r, const Hittable &object, int depth)
{
    HitRecord record;

    if (depth > 50)
    {
        return {0.0, 0.0, 0.0};
    }

    if (object.hit(r, 0.001, infinity, record))
    {
        Ray scattered = r;
        Colour attenuation;

        if (record.mtrPtr->scatter(r, record, attenuation, scattered))
        {
            return attenuation * colourRay(scattered, object, depth + 1);
        }

        return {0.0, 0.0, 0.0};
    }

    Vec3 unitDirection = unit(r.direction);
    auto t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

Camera getCamera(double aspect_ratio)
{
    Point3 lookfrom = Point3(3, 3, 2);
    Point3 lookat = Point3(0, 0, -1);
    Point3 vup = Vec3(0, 1, 0);
    double fovAngle = 20.0;
    double aperture = 2.0;
    double focusDistance = (lookfrom - lookat).length();
    bool dof = false;
    Camera cam(lookfrom, lookat, vup, fovAngle, aspect_ratio, aperture, focusDistance, dof);

    return cam;
}

HittableList getScene()
{
    //Defining objects and materials
    shared_ptr<Material> material1 = make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
    shared_ptr<Material> material2 = make_shared<Lambertian>(Colour(0.7, 0.3, 0.3));
    shared_ptr<Material> material3 = make_shared<Metal>(Colour(0.8, 0.8, 0.8), 0.001);
    shared_ptr<Material> material4 = make_shared<Metal>(Colour(0.8, 0.6, 0.2), 0.2);
    shared_ptr<Material> material5 = make_shared<Dielectric>(1.5);

    HittableList objects = HittableList();
    objects.add(make_shared<Sphere>(Point3(0.0, 0.0, -1), 0.5, material1));
    objects.add(make_shared<Sphere>(Point3(0.0, -100.5, -1), 100, material2));
    objects.add(make_shared<Sphere>(Point3(0.25, 0.25, -0.5), 0.1, material4));
    objects.add(make_shared<Sphere>(Point3(-0.25, 0.25, -0.5), 0.1, material3));
    objects.add(make_shared<Sphere>(Point3(0.0, 0.3, -0.6), 0.15, material5));

    HittableList world;

    auto materialGround = make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
    auto materialCenter = make_shared<Lambertian>(Colour(0.1, 0.2, 0.5));
    auto materialLeft = make_shared<Lambertian>(Colour(0.5, 0.2, 0.3));
    auto materialRight = make_shared<Metal>(Colour(0.8, 0.6, 0.2), 0.0);

    world.add(make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), -0.45, materialLeft));
    world.add(make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

    return world;
}

int main()
{
    //Defining image properties and Camera
    double aspectRatio = 1.0 / 1.0;
    int imgWidth = 1200;
    int imgHeight = static_cast<int>(static_cast<double>(imgWidth) / aspectRatio);
    int samplesPerPixel = 100;

    Camera cam = getCamera(aspectRatio);
    HittableList scene = getScene();

    MTL::Device *device = MTL::CreateSystemDefaultDevice();
    cout << device->name()->utf8String();

    int noOfThreads = std::thread::hardware_concurrency();

    ofstream image("../renders/image.ppm");
    if (image.is_open())
    {
        int index = 0;
        image << "P3\n" << imgWidth << ' ' << imgHeight << "\n255\n";
        for (int i = imgHeight; i > 0; i--)
        {
            for (int j = 0; j < imgWidth; j = j + noOfThreads)
            {
                mutex mutex;
                auto renderPixel = [&](int x)
                {
                    Colour pixel = Colour(0.0, 0.0, 0.0);
                    for (int s = 0; s < samplesPerPixel; s++)
                    {
                        double u = (static_cast<double>(x) + randomDouble()) / static_cast<double>(imgWidth);
                        double v = (static_cast<double>(i) + randomDouble()) / static_cast<double>(imgHeight);
                        Ray r = cam.getRay(u, v);
                        pixel += colourRay(r, scene, 1);
                    }
                    pixel *= (1.0 / static_cast<double>(samplesPerPixel));
                    return pixel;
                };
                auto outputPixel = [&](Colour pixel)
                {
                    int red = static_cast<int>(pixel.x * 255);
                    int green = static_cast<int>(pixel.y * 255);
                    int blue = static_cast<int>(pixel.z * 255);
                    mutex.lock();
                    image << red << ' ' << green << ' ' << blue << '\n';
                    cout << "Rendered: " << (index * 100) / (imgWidth * imgHeight) << '%' << " - remaining pixels: "
                         << imgWidth * imgHeight - 1 - index << '\n';
                    mutex.unlock();
                    index++;
                };

                //Concurrency
                vector<std::future<Colour>> futures;
                for (int idx = 0; idx < noOfThreads; idx++)
                {
                    futures.push_back(std::async(renderPixel, j + idx));
                }
                for (auto &f: futures)
                {
                    outputPixel(f.get());
                }
            }
        }
        image.close();
    }
    return 0;
}
