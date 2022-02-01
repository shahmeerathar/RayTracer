//
// Created by Shahmeer Athar on 2022-01-31.
//

#include "GPURenderer.h"

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

void GPURenderer::render()
{
    // Setting up Metal
    MTL::Device *mtlDevice = MTL::CreateSystemDefaultDevice();
    auto gpuName = mtlDevice->name()->utf8String();
    cout << "Rendering on " << gpuName << endl;

    MTL::CommandQueue *commandQueue = mtlDevice->newCommandQueue();
    MTL::Library *defaultLibrary = mtlDevice->newDefaultLibrary();
    MTL::Function *rayTracing = defaultLibrary->newFunction(reinterpret_cast<const NS::String *>("rayTracing"));
    NS::Error **nsError;
    MTL::ComputePipelineState *rtPipelineState = mtlDevice->newComputePipelineState(rayTracing, nsError);

    int threadsPerGroupWidth = rtPipelineState->threadExecutionWidth();
    int threadsPerGroupHeight = rtPipelineState->maxTotalThreadsPerThreadgroup() / threadsPerGroupWidth;
    MTL::Size threadsPerGroup = MTL::Size(threadsPerGroupWidth, threadsPerGroupHeight, 1);
    MTL::Size threadsPerGrid = MTL::Size(m_ImageProperties.imgWidth, m_ImageProperties.imgHeight, 1);
    MTL::CommandBuffer *commandBuffer = commandQueue->commandBuffer();
    MTL::ComputeCommandEncoder *encoder = commandBuffer->computeCommandEncoder();
    encoder->setComputePipelineState(rtPipelineState);

    encoder->dispatchThreads(threadsPerGrid, threadsPerGroup);
    encoder->endEncoding();
    commandBuffer->commit();
    commandBuffer->waitUntilCompleted();
}
