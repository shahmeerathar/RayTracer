#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class vec3
{
    public:
    double x, y, z;
    vec3(double e1 = 0.0, double e2 = 0.0, double e3 = 0.0)
    {
        x = e1;
        y = e2;
        z = e3;
    }
    vec3(int e1 = 0, int e2 = 0, int e3 = 0)
    {
        x = double(e1);
        y = double(e2);
        z = double(e3);
    }

    vec3 operator-() const
    {
        return vec3(-x, -y, -z);
    }

    void operator+=(const vec3 &vec)
    {
        x = x + vec.x;
        y = y + vec.y;
        z = z + vec.z;
    }

    void operator-=(const vec3 &vec)
    {
        *this+=(-vec);
    }

    void operator*=(const double t)
    {
        x = x * t;
        y = y * t;
        z = z * t;
    }

    void operator/=(const double t)
    {
        *this*=(1/t);
    }

    double length_squared() const
    {
        return (x*x + y*y + z*z);
    }

    double length() const
    {
        return sqrt(length_squared());
    }
};

using point3 = vec3;
using colour = vec3;

//Vector3 utility functions:
inline ostream& operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.x << ' ' << v.y << ' ' << v.z << '\n';
}

inline vec3 operator+(const vec3 &a, const vec3 &b)
{
    return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline vec3 operator-(const vec3 &a, const vec3 &b)
{
    return a + (-b);
}

inline vec3 operator*(const vec3 &a, const vec3 &b)
{
    return vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline vec3 operator*(const vec3 &a, double t)
{
    return vec3(a.x * t, a.y * t, a.z * t);
}

inline vec3 operator*(double t, const vec3 &a)
{
    return a*t;
}

inline vec3 operator/(const vec3 &a, double t)
{
    return a*(1/t);
}

inline double dot(const vec3 &a, const vec3 &b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

inline vec3 cross(const vec3 &a, const vec3 &b)
{
    return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y-a.y*b.x);
}

inline vec3 unit(const vec3 &a)
{
    return a / a.length();
}


void write_ppm()
{
    ofstream image ("image.ppm");
    if (image.is_open())
    {
        int width = 256;
        int height = 256;
        int remaining = width * height;
        image << "P3\n" << width << ' ' << height << "\n255\n";
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                double red = (double(i) / double(height)) * 255;
                double green = (double(j) / double(width)) * 255;
                image << int(red) << ' ' << int(green) << ' ' << 100 << '\n';
                cout << "Pixels remaining: " << remaining << '\n';
                remaining--;
            }
        }
        image.close();
    }
}

int main()
{
    write_ppm();
    return 0;
}