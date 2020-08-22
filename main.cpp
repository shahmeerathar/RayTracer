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
        image << "P3\n" << width << ' ' << height << "\n255\n";
        for (int i = 0; i <= 255; i++)
        {
            for (int j = 0; j <= 255; j++)
            {
                image << i << ' ' << j << ' ' << 100 << '\n';
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