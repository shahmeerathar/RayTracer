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
    scattered = ray(record.point, reflected_direction + fuzz * random_unit_vector());
    attenuation = albedo;
    return (dot(scattered.direction, record.normal) > 0);
}

dielectric::dielectric(double ri)
{
    refractive_index = ri;
}

bool dielectric::scatter(const ray& in_ray, const hit_record& record, colour& attenuation, ray& scattered) const
{
    attenuation = colour(1.0, 1.0, 1.0);
    double index = record.front_face ? (1.0 / refractive_index) : refractive_index;
    double cos_theta = fmin(dot(-unit(in_ray.direction), unit(record.normal)), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);
    if ((index * sin_theta > 1.0) || (random_double() < schlick(cos_theta, index)))
    {
        vec3 reflected = reflect(unit(in_ray.direction), record.normal);
        scattered = ray(record.point, reflected);
        return true;
    }
    vec3 refracted = refract(unit(in_ray.direction), record.normal, index);
    scattered = ray(record.point, refracted);
    return true;
}