//
// Created by Shahmeer Athar on 2022-01-31.
//

#include "GPURenderer.h"

#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <QuartzCore/QuartzCore.hpp>

void GPURenderer::render()
{
    MTL::Device *device = MTL::CreateSystemDefaultDevice();
    auto gpuName = device->name()->utf8String();

    cout << "Rendering on " << gpuName << endl;
}
