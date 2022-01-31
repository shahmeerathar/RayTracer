#pragma once

#include "commons.h"

class Camera
{
public:
    double angle;
    double aspectRatio;
    double width;
    double height;
    double focusDistance;
    vec3 z;
    vec3 x;
    vec3 y;
    point3 origin;
    vec3 horizontal;
    vec3 vertical;
    point3 lowerLeftCorner;
    double lensRadius;
    bool dof;

    Camera(point3 from, point3 to, point3 up, double deg, double aspect, double aperture, double fd, bool dofFlag);
    ray getRay(double u, double v);
};