//
// Created by Shahmeer Athar on 2022-01-31.
//

#ifndef RAYTRACER_CPURENDERER_H
#define RAYTRACER_CPURENDERER_H


#include "Renderer.h"

class CPURenderer
        : public Renderer
{
public:
    CPURenderer(const ImageProperties &imageProperties, const Camera &camera, const HittableList &scene)
            : Renderer(imageProperties, camera, scene)
    {}

    void render() override;
};


#endif //RAYTRACER_CPURENDERER_H
