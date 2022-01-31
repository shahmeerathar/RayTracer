#pragma once
#include "commons.h"

class camera
{
    public:
    
    double angle;
    double aspect_ratio;
    double width;
    double height;
    double focus_distance;
    vec3 z;
    vec3 x;
    vec3 y;
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    point3 lower_left_corner;
    double lens_radius;
    bool dof;

    camera(point3 from, point3 to, point3 up, double deg, double aspect, double aperture, double fd, bool dof_flag);
    ray get_ray(double u, double v);
};