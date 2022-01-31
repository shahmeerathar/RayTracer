#pragma once

#include <iostream>
#include <cmath>

using namespace std;

class Vec3
{
public:
    double x, y, z;

    Vec3(double e1 = 0.0, double e2 = 0.0, double e3 = 0.0);
    Vec3 operator-() const;
    void operator+=(const Vec3 &vec);
    void operator-=(const Vec3 &vec);
    void operator*=(double t);
    void operator/=(double t);
    double lengthSquared() const;
    double length() const;
};

using Point3 = Vec3;
using Colour = Vec3;


//Vector3 utility functions:
inline ostream &operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z << '\n';
}

inline Vec3 operator+(const Vec3 &a, const Vec3 &b)
{
    return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline Vec3 operator-(const Vec3 &a, const Vec3 &b)
{
    return a + (-b);
}

inline Vec3 operator*(const Vec3 &a, const Vec3 &b)
{
    return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline Vec3 operator*(const Vec3 &a, double t)
{
    return Vec3(a.x * t, a.y * t, a.z * t);
}

inline Vec3 operator*(double t, const Vec3 &a)
{
    return a * t;
}

inline Vec3 operator/(const Vec3 &a, double t)
{
    return a * (1 / t);
}

inline double dot(const Vec3 &a, const Vec3 &b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

inline Vec3 cross(const Vec3 &a, const Vec3 &b)
{
    return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline Vec3 unit(const Vec3 &a)
{
    return a / a.length();
}