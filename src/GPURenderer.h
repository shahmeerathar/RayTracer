//
// Created by Shahmeer Athar on 2022-01-31.
//

#ifndef RAYTRACER_GPURENDERER_H
#define RAYTRACER_GPURENDERER_H


#include "Renderer.h"

class GPURenderer
        : public Renderer
{
public:
    GPURenderer(const ImageProperties &imageProperties, const Camera &camera, const HittableList &scene)
            : Renderer(imageProperties, camera, scene)
    {}

    void render() override;
};


#endif //RAYTRACER_GPURENDERER_H
