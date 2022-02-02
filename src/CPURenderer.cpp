//
// Created by Shahmeer Athar on 2022-01-31.
//

#include "CPURenderer.h"
#include "Materials.h"

#include <iostream>
#include <fstream>
#include <cmath>
#include <thread>
#include <mutex>
#include <future>

Colour CPURenderer::colourRay(const Ray &r, const Hittable &object, int depth)
{
    HitRecord record;

    if (depth > 50)
    {
        return Colour(0.0, 0.0, 0.0);
    }

    if (object.hit(r, 0.001, infinity, record))
    {
        Ray scattered = r;
        Colour attenuation;

        if (record.mtrPtr->scatter(r, record, attenuation, scattered))
        {
            return attenuation * colourRay(scattered, object, depth + 1);
        }

        return Colour(0.0, 0.0, 0.0);
    }

    Vec3 unitDirection = unit(r.direction);
    auto t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

void CPURenderer::render()
{
    cout << "Rendering on the CPU\n";

    int noOfThreads = std::thread::hardware_concurrency();

    ofstream image("../renders/image.ppm");
    if (image.is_open())
    {
        int index = 0;
        image << "P3\n" << m_ImageProperties.imgWidth << ' ' << m_ImageProperties.imgHeight << "\n255\n";
        for (int i = m_ImageProperties.imgHeight; i > 0; i--)
        {
            for (int j = 0; j < m_ImageProperties.imgWidth; j = j + noOfThreads)
            {
                mutex mutex;
                auto renderPixel = [&](int x)
                {
                    Colour pixel = Colour(0.0, 0.0, 0.0);
                    for (int s = 0; s < m_ImageProperties.samplesPerPixel; s++)
                    {
                        double u = (static_cast<double>(x) + randomDouble()) /
                                   static_cast<double>(m_ImageProperties.imgWidth);
                        double v = (static_cast<double>(i) + randomDouble()) /
                                   static_cast<double>(m_ImageProperties.imgHeight);
                        Ray r = m_Camera.getRay(u, v);
                        pixel += colourRay(r, m_Scene, 1);
                    }
                    pixel *= (1.0 / static_cast<double>(m_ImageProperties.samplesPerPixel));
                    return pixel;
                };
                auto outputPixel = [&](Colour pixel)
                {
                    int red = static_cast<int>(pixel.x * 255);
                    int green = static_cast<int>(pixel.y * 255);
                    int blue = static_cast<int>(pixel.z * 255);
                    mutex.lock();
                    image << red << ' ' << green << ' ' << blue << '\n';
                    cout << "Rendered: " << (index * 100) / (m_ImageProperties.imgWidth * m_ImageProperties.imgHeight)
                         << '%' << " - remaining pixels: "
                         << m_ImageProperties.imgWidth * m_ImageProperties.imgHeight - 1 - index << '\n';
                    mutex.unlock();
                    index++;
                };

                //Concurrency
                vector<std::future<Colour> > futures;
                for (int idx = 0; idx < noOfThreads; idx++)
                {
                    futures.push_back(std::async(renderPixel, j + idx));
                }
                for (auto &f: futures)
                {
                    outputPixel(f.get());
                }
            }
        }
        image.close();
    }
}
