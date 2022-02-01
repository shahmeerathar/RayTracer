//
// Created by Shahmeer Athar on 2022-01-31.
//

#include "GPURenderer.h"
#include "GPURayTracer.h"

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

    NS::Error **nsError;
    MTL::CommandQueue *commandQueue = mtlDevice->newCommandQueue();
    auto libraryData = dispatch_data_create(&lib_GPURayTracer_metallib[0], lib_GPURayTracer_metallib_len,
                                            dispatch_get_current_queue(), ^
                                            {});
    MTL::Library *mtlLibrary = mtlDevice->newLibrary(libraryData, nsError);
    NS::String *kernelFunctionName = NS::String::string("rayTrace", NS::ASCIIStringEncoding);
    MTL::Function *rayTracingFunction = mtlLibrary->newFunction(kernelFunctionName);
    MTL::ComputePipelineState *rtPipelineState = mtlDevice->newComputePipelineState(rayTracingFunction, nsError);

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
