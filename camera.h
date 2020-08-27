#pragma once
#include "commons.h"

class camera
{
    public:
    
    double width;
    double height;
    double focal_length;
    int samples_per_pixel;
    point3 origin;
    vec3 horizonal;
    vec3 vertical;
    point3 lower_left;

    camera(double w, double aspect, double focal, int samples);
    ray get_ray(double u, double v);
};