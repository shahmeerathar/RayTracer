#include "camera.h"

camera::camera(point3 from, point3 to, point3 up, double deg, double aspect, double aperture, double fd, bool dof_flag)
{
    angle = deg;
    aspect_ratio = aspect;
    height = 2.0 * tan(deg_to_rad(angle)/2);;
    width = height * aspect_ratio;
    dof = dof_flag;
    if (dof)
    {
        focus_distance = fd;
    }
    else
    {
        focus_distance = 1;
    }
    

    z = unit(from - to);
    x = unit(cross(-z, up));
    y = unit(cross(z, x));

    origin = from;
    horizontal = focus_distance * x * width;
    vertical = focus_distance * y * height;
    lower_left_corner = origin - horizontal/2 - vertical/2 - (focus_distance * z);

    lens_radius = aperture / 2;
}

ray camera::get_ray(double u, double v)
{
    if (dof)
    {
        vec3 disc_point = lens_radius * random_in_unit_disk();
        vec3 offset = (x * disc_point.x) + (y * disc_point.y);
        return ray(origin + offset, lower_left_corner + u*horizontal + v*vertical - origin - offset);
    }
    else
    {
        return ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
    }
}