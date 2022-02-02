//
// Created by Shahmeer Athar on 2022-01-31.
//

#ifndef RAYTRACER_RENDERER_H
#define RAYTRACER_RENDERER_H


#include "Camera.h"
#include "HittableList.h"
#include "Vec3.h"

struct ImageProperties
{
    double aspectRatio;
    int imgWidth;
    int imgHeight;
    int samplesPerPixel;
} typedef ImageProperties;

class Renderer
{
public:
    Renderer(ImageProperties imageProperties, Camera camera, HittableList scene) : m_ImageProperties(imageProperties),
                                                                                   m_Camera(camera),
                                                                                   m_Scene(scene)
    {}

    virtual void render() = 0;

protected:
    ImageProperties m_ImageProperties;
    Camera m_Camera;
    HittableList m_Scene;
};


#endif //RAYTRACER_RENDERER_H
