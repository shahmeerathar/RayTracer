#include <iostream>
#include <fstream>
using namespace std;

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