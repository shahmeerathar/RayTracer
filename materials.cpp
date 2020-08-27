#include "materials.h"

bool Lambertian::scatter(const ray& in_ray, const hit_record& record, colour& attenuation, ray& scattered) const
{
    vec3 scatter_direction = record.point + record.normal + random_unit_vector();
    scattered = ray(record.point, scatter_direction);
    attenuation = albedo;
    return true;
}

bool metal::scatter(const ray& in_ray, const hit_record& record, colour& attenuation, ray& scattered) const
{
    vec3 reflected_direction = reflect(unit(in_ray.direction), record.normal);
    scattered = ray(record.point, reflected_direction + random_double(0.3, 1.0) * random_unit_vector());
    attenuation = albedo;
    return (dot(scattered.direction, record.normal) > 0);
}