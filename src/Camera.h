#pragma once

#include "Commons.h"

class Camera
{
public:
    double angle;
    double aspectRatio;
    double width;
    double height;
    double focusDistance;
    Vec3 z;
    Vec3 x;
    Vec3 y;
    Point3 origin;
    Vec3 horizontal;
    Vec3 vertical;
    Point3 lowerLeftCorner;
    double lensRadius;
    bool dof;

    Camera(Point3 from, Point3 to, Point3 up, double deg, double aspect, double aperture, double fd, bool dofFlag);
    Ray getRay(double u, double v);
};