#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


void write_ppm(colour pixels[], int width, int height)
{
    ofstream image ("image.ppm");
    if (image.is_open())
    {
        int index = 0;
        image << "P3\n" << width << ' ' << height << "\n255\n";
        for (int i = 0; i < width * height; i++)
        {
            colour pixel = pixels[i];
            int red = static_cast<int>(pixel.x * 255);
            int green = static_cast<int>(pixel.y * 255);
            int blue = static_cast<int>(pixel.z * 255);
            image << red << ' ' << green << ' ' << blue << '\n';
        }
        image.close();
    }
}

int main()
{
    //Defining image properties
    double aspect_ratio = 1.0 / 1.0;
    int img_width  = 256;
    int img_height = static_cast<int>(static_cast<double>(img_width) / aspect_ratio);

    //Defining camera and viewing plane
    double viewport_width = 2.0;
    double viewport_height = viewport_width / aspect_ratio;
    double focal_length = 1.0;

    point3 origin = point3(0.0, 0.0, 0.0);
    vec3 horizontal = vec3(viewport_width, 0.0, 0.0);
    vec3 vertical = vec3(0.0, viewport_height, 0.0);
    point3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0.0, 0.0, focal_length);

    colour pixels[img_width * img_height];

    int index = 0;
    for (int i = img_height; i > 0; i--)
        {
            for (int j = 0; j < img_width; j++)
            {
                double u = static_cast<double>(j) / static_cast<double>(img_width);
                double v = static_cast<double>(i) / static_cast<double>(img_height);
                ray r = ray(origin, lower_left_corner + u*horizontal + v*vertical);
                sphere s = sphere(point3(0.0, 0.0, -0.5), 0.4);
                pixels[index] = r.colour_ray(s);
                cout << "Remaining: " << img_width*img_height - 1 - index << '\n';
                index++;
            }
        }

    write_ppm(pixels, img_width, img_height);
    return 0;
}
