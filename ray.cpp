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