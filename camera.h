#pragma once
#include "commons.h"

class camera
{
    public:
    
    double angle;
    double aspect_ratio;
    double width;
    double height;
    double focal_length;
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    point3 lower_left_corner;

    camera(double w, double aspect, double focal);
    ray get_ray(double u, double v);
};