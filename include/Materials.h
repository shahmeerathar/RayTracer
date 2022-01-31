#pragma once

#include "Hittable.h"

struct HitRecord;

class Material
{
public:
    virtual bool scatter(const Ray &inRay, const HitRecord &record, Colour &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Colour albedo;

    Lambertian(const Colour &a);
    bool scatter(const Ray &inRay, const HitRecord &record, Colour &attenuation, Ray &scattered) const override;
};

class Metal : public Material
{
public:
    Colour albedo;
    double fuzz;

    Metal(const Colour &a, double f);
    bool scatter(const Ray &inRay, const HitRecord &record, Colour &attenuation, Ray &scattered) const override;
};

class Dielectric : public Material
{
public:
    double refractiveIndex;

    Dielectric(double ri);
    bool scatter(const Ray &inRay, const HitRecord &record, Colour &attenuation, Ray &scattered) const override;
};