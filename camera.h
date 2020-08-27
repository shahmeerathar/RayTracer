#pragma once
#include "commons.h"

class camera
{
    public:
    
    double angle;
    double aspect_ratio;
    double width;
    double height;
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    point3 lower_left_corner;

    camera(point3 from, point3 to, point3 up, double deg, double aspect);
    ray get_ray(double u, double v);
};