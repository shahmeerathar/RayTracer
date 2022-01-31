#include "Commons.h"
#include "Camera.h"
#include "Sphere.h"
#include "HittableList.h"
#include "Materials.h"
#include "CPURenderer.h"

#if defined(__APPLE__)

#include "GPURenderer.h"

#endif

using namespace std;

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
    //Defining image properties and camera
    ImageProperties imageProperties;
    imageProperties.aspectRatio = 1.0 / 1.0;
    imageProperties.imgWidth = 1200;
    imageProperties.imgHeight = static_cast<int>(static_cast<double>(imageProperties.imgWidth) /
                                                 imageProperties.aspectRatio);
    imageProperties.samplesPerPixel = 100;

#if defined(__APPLE__)
    GPURenderer renderer(imageProperties, getCamera(imageProperties.aspectRatio), getScene());
#else
    CPURenderer renderer(imageProperties, getCamera(imageProperties.aspectRatio), getScene());
#endif

    renderer.render();

    return 0;
}
