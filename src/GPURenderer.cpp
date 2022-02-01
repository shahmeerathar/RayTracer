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
    // Setting up Metal device and command queue
    NS::Error *nsError;
    MTL::Device *mtlDevice = MTL::CreateSystemDefaultDevice();
    MTL::CommandQueue *commandQueue = mtlDevice->newCommandQueue();
    cout << "Rendering on " << mtlDevice->name()->utf8String() << endl;

    // Load Metal library
    NS::String *metalLibFilePath = NS::String::string("../lib/GPURayTracer.metallib", NS::UTF8StringEncoding);
    MTL::Library *mtlLibrary = mtlDevice->newLibrary(metalLibFilePath, &nsError);
    if (nsError)
    {
        cout << "Couldn't load library: " << nsError->description()->utf8String() << endl;
        return;
    }
    cout << "Loaded Metal ray tracing library" << endl;

    // Load ray tracing shader
    NS::String *kernelFunctionName = NS::String::string("rayTrace", NS::ASCIIStringEncoding);
    MTL::Function *rayTracingFunction = mtlLibrary->newFunction(kernelFunctionName);
    if (!rayTracingFunction)
    {
        cout << "Could not load ray tracing function :(" << endl;
        return;
    }
    cout << "Loaded function " << rayTracingFunction->name()->utf8String() << " from Metal library" << endl;

    // Set up compute shader pipeline state and thread parameters
    MTL::ComputePipelineState *rtPipelineState = mtlDevice->newComputePipelineState(rayTracingFunction, &nsError);
    if (nsError)
    {
        cout << "Couldn't set up compute pipeline state: " << nsError->description()->utf8String() << endl;
        return;
    }
    cout << "Set up Metal compute pipeline state" << endl;
    int threadsPerGroupWidth = rtPipelineState->threadExecutionWidth();
    int threadsPerGroupHeight = rtPipelineState->maxTotalThreadsPerThreadgroup() / threadsPerGroupWidth;
    MTL::Size threadsPerGroup = MTL::Size(threadsPerGroupWidth, threadsPerGroupHeight, 1);
    MTL::Size threadsPerGrid = MTL::Size(m_ImageProperties.imgWidth, m_ImageProperties.imgHeight, 1);

    // Set up command buffer and encoder
    MTL::CommandBuffer *commandBuffer = commandQueue->commandBuffer();
    MTL::ComputeCommandEncoder *encoder = commandBuffer->computeCommandEncoder();
    encoder->setComputePipelineState(rtPipelineState);

    // Dispatch kernel
    encoder->dispatchThreads(threadsPerGrid, threadsPerGroup);
    encoder->endEncoding();
    commandBuffer->commit();
    commandBuffer->waitUntilCompleted();

    cout << "Render complete!";
}
