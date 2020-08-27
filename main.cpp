#include "commons.h"
#include "camera.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"
#include "materials.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

colour colour_ray(const ray& r, const hittable& object, int depth)
{
	hit_record record;

    if (depth > 50)
    {
        return colour(0.0, 0.0, 0.0);
    }

	if (object.hit(r, 0.001, infinity, record))
	{
        ray scattered = r;
        colour attenuation;
        if (record.mtr_ptr->scatter(r, record, attenuation, scattered))
        {
            return attenuation * colour_ray(scattered, object, depth + 1);
        }
        return colour(0.0, 0.0, 0.0);
	}
    vec3 unit_direction = unit(r.direction);
    auto t = 0.5*(unit_direction.y + 1.0);
    return (1.0-t)*colour(1.0, 1.0, 1.0) + t*colour(0.5, 0.7, 1.0);
}

int main()
{
    //Defining image properties and camera
    double aspect_ratio = 16.0/9.0;
    int img_width  = 500;
    int img_height = static_cast<int>(static_cast<double>(img_width) / aspect_ratio);
    int samples_per_pixel = 100;

    point3 lookfrom = point3(2,1,1);
    point3 lookat = point3(0,0,-1);
    point3 vup = vec3(-0.25,1.25,0);
    double fov_angle = 20.0;
    double aperture = 6.0;
    double focus_distance = (lookfrom - lookat).length();
    camera cam(lookfrom, lookat, vup, fov_angle, aspect_ratio, aperture, focus_distance);

    //Defining objects and materials
    shared_ptr<material> material_1 = make_shared<Lambertian>(colour(0.8, 0.8, 0.0));
    shared_ptr<material> material_2 = make_shared<Lambertian>(colour(0.7, 0.3, 0.3));
    shared_ptr<material> material_3 = make_shared<metal>(colour(0.8, 0.8, 0.8), 0.001);
    shared_ptr<material> material_4 = make_shared<metal>(colour(0.8, 0.6, 0.2), 0.2);
    shared_ptr<material> material_5 = make_shared<dielectric>(1.5);

    hittable_list objects = hittable_list();
    objects.add(make_shared<sphere>(point3(0.0, 0.0, -1), 0.5, material_1));
    objects.add(make_shared<sphere>(point3(0.0, -100.5, -1), 100, material_2));
    objects.add(make_shared<sphere>(point3(0.25, 0.25, -0.5), 0.1, material_4));
    objects.add(make_shared<sphere>(point3(-0.25, 0.25, -0.5), 0.1, material_3));
    objects.add(make_shared<sphere>(point3(0.0, 0.3, -0.6), 0.15, material_5));

    //Iterating through pixels
    int index = 0;

    ofstream image ("image.ppm");
    if (image.is_open())
    {
        int index = 0;
        image << "P3\n" << img_width << ' ' << img_height << "\n255\n";
        for (int i = img_height; i > 0; i--)
        {
            for (int j = 0; j < img_width; j++)
            {
                colour pixel = colour(0.0, 0.0, 0.0);
                for (int s = 0; s < samples_per_pixel; s++)
                {
                    double u = (static_cast<double>(j) + random_double()) / static_cast<double>(img_width);
                    double v = (static_cast<double>(i) + random_double()) / static_cast<double>(img_height);
                    ray r = cam.get_ray(u, v);
                    pixel += colour_ray(r, objects, 1);
                }
                pixel *= (1.0 / static_cast<double>(samples_per_pixel));
                int red = static_cast<int>(pixel.x * 255);
                int green = static_cast<int>(pixel.y * 255);
                int blue = static_cast<int>(pixel.z * 255);
                image << red << ' ' << green << ' ' << blue << '\n';
                cout << "Rendered: " << (index*100)/(img_width*img_height) << '%' << " - remaining pixels: " << img_width*img_height - 1 - index << '\n';
                index++;
            }
        }
        image.close();
    }
    return 0;
}
