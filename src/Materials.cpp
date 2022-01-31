#include "Materials.h"

Lambertian::Lambertian(const colour &a)
{
    albedo = a;
}

bool Lambertian::scatter(const ray& inRay, const HitRecord& record, colour& attenuation, ray& scattered) const
{
    vec3 scatterDirection = record.point + record.normal + randomUnitVector();
    scattered = ray(record.point, scatterDirection);
    attenuation = albedo;
    return true;
}

Metal::Metal(const colour &a, double f)
{
    albedo = a;
    fuzz = f;
}

bool Metal::scatter(const ray& inRay, const HitRecord& record, colour& attenuation, ray& scattered) const
{
    vec3 reflectedDirection = reflect(unit(inRay.direction), record.normal);
    scattered = ray(record.point, reflectedDirection + fuzz * randomUnitVector());
    attenuation = albedo;
    return (dot(scattered.direction, record.normal) > 0);
}

Dielectric::Dielectric(double ri)
{
    refractiveIndex = ri;
}

bool Dielectric::scatter(const ray& inRay, const HitRecord& record, colour& attenuation, ray& scattered) const
{
    attenuation = colour(1.0, 1.0, 1.0);
    double index = record.frontFace ? (1.0 / refractiveIndex) : refractiveIndex;
    double cosTheta = fmin(dot(-unit(inRay.direction), unit(record.normal)), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    if ((index * sinTheta > 1.0) || (randomDouble() < schlick(cosTheta, index)))
    {
        vec3 reflected = reflect(unit(inRay.direction), record.normal);
        scattered = ray(record.point, reflected);
        return true;
    }
    vec3 refracted = refract(unit(inRay.direction), record.normal, index);
    scattered = ray(record.point, refracted);
    return true;
}