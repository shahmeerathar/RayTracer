#include "camera.h"
#include <iostream>

camera::camera(double w, double aspect_ratio, double length, int samples)
{
    width = w;
    height = width / aspect_ratio;
    focal_length = length;
    samples_per_pixel = samples;

    origin = point3(0.0, 0.0, 0.0);
    horizontal = vec3(width, 0.0, 0.0);
    vertical = vec3(0.0, height, 0.0);
    lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0.0, 0.0, focal_length);
}

ray camera::get_ray(double u, double v)
{
    return ray(origin, lower_left_corner + u*horizontal + v*vertical);
}