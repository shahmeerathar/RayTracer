#include "camera.h"

camera::camera(double w, double aspect_ratio, double length, int samples)
{
    width = w;
    height = width / aspect_ratio;
    focal_length = length;
    samples_per_pixel = samples;

    point3 origin = point3(0.0, 0.0, 0.0);
    vec3 horizontal = vec3(width, 0.0, 0.0);
    vec3 vertical = vec3(0.0, height, 0.0);
    point3 lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0.0, 0.0, focal_length);
}

ray camera::get_ray(double u, double v)
{
    return ray(origin, lower_left + u*horizonal + v*vertical);
}