#include "camera.h"
#include <iostream>

camera::camera(point3 from, point3 to, point3 up, double deg, double aspect)
{
    angle = deg;
    aspect_ratio = aspect;
    height = 2.0 * tan(deg_to_rad(angle)/2);;
    width = height * aspect_ratio;

    vec3 z = unit(from - to);
    vec3 x = unit(cross(-z, up));
    vec3 y = unit(cross(z, x));

    origin = from;
    horizontal = x * width;
    vertical = y * height;
    lower_left_corner = origin - horizontal/2 - vertical/2 - z;
}

ray camera::get_ray(double u, double v)
{
    return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}