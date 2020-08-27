#include "camera.h"
#include <iostream>

camera::camera(double deg, double aspect, double focal)
{
    angle = deg;
    aspect_ratio = aspect;
    height = 2.0 * tan(deg_to_rad(angle)/2);;
    width = height * aspect_ratio;
    focal_length = focal;

    origin = point3(0.0, 0.0, 0.0);
    horizontal = vec3(width, 0.0, 0.0);
    vertical = vec3(0.0, height, 0.0);
    lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0.0, 0.0, focal_length);
}

ray camera::get_ray(double u, double v)
{
    return ray(origin, lower_left_corner + u*horizontal + v*vertical);
}