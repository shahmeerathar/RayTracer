#include "Camera.h"

Camera::Camera(point3 from, point3 to, point3 up, double deg, double aspect, double aperture, double fd, bool dofFlag)
{
    angle = deg;
    aspectRatio = aspect;
    height = 2.0 * tan(degToRad(angle) / 2);;
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

Ray Camera::getRay(double u, double v)
{
    if (dof)
    {
        vec3 discPoint = lensRadius * randomInUnitDisk();
        vec3 offset = (x * discPoint.x) + (y * discPoint.y);
        return Ray(origin + offset, lowerLeftCorner + u * horizontal + v * vertical - origin - offset);
    } else
    {
        return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
    }
}