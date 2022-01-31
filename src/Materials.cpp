#include "Materials.h"

Lambertian::Lambertian(const Colour &a)
{
    albedo = a;
}

bool Lambertian::scatter(const Ray &inRay, const HitRecord &record, Colour &attenuation, Ray &scattered) const
{
    Vec3 scatterDirection = record.point + record.normal + randomUnitVector();
    scattered = Ray(record.point, scatterDirection);
    attenuation = albedo;
    return true;
}

Metal::Metal(const Colour &a, double f)
{
    albedo = a;
    fuzz = f;
}

bool Metal::scatter(const Ray &inRay, const HitRecord &record, Colour &attenuation, Ray &scattered) const
{
    Vec3 reflectedDirection = reflect(unit(inRay.direction), record.normal);
    scattered = Ray(record.point, reflectedDirection + fuzz * randomUnitVector());
    attenuation = albedo;
    return (dot(scattered.direction, record.normal) > 0);
}

Dielectric::Dielectric(double ri)
{
    refractiveIndex = ri;
}

bool Dielectric::scatter(const Ray &inRay, const HitRecord &record, Colour &attenuation, Ray &scattered) const
{
    attenuation = Colour(1.0, 1.0, 1.0);
    double index = record.frontFace ? (1.0 / refractiveIndex) : refractiveIndex;
    double cosTheta = fmin(dot(-unit(inRay.direction), unit(record.normal)), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    if ((index * sinTheta > 1.0) || (randomDouble() < schlick(cosTheta, index)))
    {
        Vec3 reflected = reflect(unit(inRay.direction), record.normal);
        scattered = Ray(record.point, reflected);
        return true;
    }
    Vec3 refracted = refract(unit(inRay.direction), record.normal, index);
    scattered = Ray(record.point, refracted);
    return true;
}