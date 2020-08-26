#include "ray.h"

ray::ray(const point3& ori, const vec3& dir)
{
	origin = ori;
	direction = dir;
}
	
point3 ray::at(double t) const
{
	return origin + t * direction;
}

colour ray::colour_ray(const hittable& object)
{
	hit_record record;
	if (object.hit(*this, 0, 1000, record))
	{
		return colour(1.0, 0.0, 0.0);
	}
    return colour(1.0, 1.0, 1.0);
}