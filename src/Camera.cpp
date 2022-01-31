#include "Camera.h"

Camera::Camera(point3 from, point3 to, point3 up, double deg, double aspect, double aperture, double fd, bool dofFlag)
{
    angle = deg;
    aspectRatio = aspect;
    height = 2.0 * tan(deg_to_rad(angle) / 2);;
    width = height * aspectRatio;
    dof = dofFlag;
    if (dof)
    {
        focusDistance = fd;
    } else
    {
        focusDistance = 1;
    }

    z = unit(from - to);
    x = unit(cross(-z, up));
    y = unit(cross(z, x));

    origin = from;
    horizontal = focusDistance * x * width;
    vertical = focusDistance * y * height;
    lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - (focusDistance * z);

    lensRadius = aperture / 2;
}

ray Camera::getRay(double u, double v)
{
    if (dof)
    {
        vec3 discPoint = lensRadius * random_in_unit_disk();
        vec3 offset = (x * discPoint.x) + (y * discPoint.y);
        return ray(origin + offset, lowerLeftCorner + u * horizontal + v * vertical - origin - offset);
    } else
    {
        return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
    }
}