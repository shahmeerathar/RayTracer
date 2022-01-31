#pragma once

#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <limits>
#include <memory>
#include "Vec3.h"
#include "Ray.h"

using namespace std;

const double infinity = numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degToRad(double degrees)
{
    return pi * degrees / 180.0;
}

inline double radToDeg(double rad)
{
    return 180.0 * rad / pi;
}

inline double randomDouble()
{
    return rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max)
{
    return min + (randomDouble() * (max - min));
}

inline double clamp(double x, double min, double max)
{
    if (x > max)
    {
        return max;
    }

    if (x < min)
    {
        return min;
    }

    return x;
}

inline Vec3 randomUnitVector()
{
    double a = randomDouble(0, 2 * pi);
    double z = randomDouble(-1, 1);
    double r = sqrt(1 - z * z);
    return Vec3(r * cos(a), r * sin(a), z);
}

inline Vec3 reflect(const Vec3 &v, const Vec3 &n)
{
    return unit(v - 2 * dot(v, n) * n);
}

inline Vec3 refract(const Vec3 &inRay, const Vec3 &normal, double &indexRatio)
{
    Vec3 rPerp = indexRatio * (inRay + (dot(-unit(inRay), unit(normal)) * normal));
    Vec3 rParr = -sqrt(fabs(1 - rPerp.lengthSquared())) * normal;
    return rPerp + rParr;
}

inline double schlick(double index, double cosine)
{
    double f0 = (index - 1) / (index + 1);
    f0 = f0 * f0;
    return f0 + ((1 - f0) * pow(1 - cosine, 5));
}

inline Vec3 randomInUnitDisk()
{
    while (true)
    {
        auto p = Vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}