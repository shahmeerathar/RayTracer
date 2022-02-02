//
// Created by Shahmeer Athar on 2022-01-31.
//

#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include "GPURenderer.h"

#include <iostream>
#include <fstream>

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

struct PixelProperties
{
    MTL::PixelFormat pixelFormat = MTL::PixelFormatRGBA32Float;
    int pixelComponentSize = 4;
    int componentsPerPixel = 4;
    int bytesPerPixel = pixelComponentSize * componentsPerPixel;
} typedef PixelProperties;

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

    // Set up texture for our ray tracing shader
    PixelProperties pixelProperties;
    MTL::TextureDescriptor *textureDescriptor = MTL::TextureDescriptor::alloc()->init();
    textureDescriptor->setPixelFormat(pixelProperties.pixelFormat);
    textureDescriptor->setWidth(m_ImageProperties.imgWidth);
    textureDescriptor->setHeight(m_ImageProperties.imgHeight);
    textureDescriptor->setUsage(MTL::TextureUsageShaderWrite);
    textureDescriptor->setStorageMode(MTL::StorageModeShared);
    MTL::Texture *texture = mtlDevice->newTexture(textureDescriptor);

    // Encode parameters into kernel
    encoder->setTexture(texture, 0);
    encoder->setBytes(&m_ImageProperties.imgWidth, sizeof(int), 0);
    encoder->setBytes(&m_ImageProperties.imgHeight, sizeof(int), 1);
    encoder->setBytes(&m_ImageProperties.samplesPerPixel, sizeof(int), 2);

    // Dispatch kernel
    encoder->dispatchThreads(threadsPerGrid, threadsPerGroup);
    encoder->endEncoding();
    commandBuffer->commit();
    commandBuffer->waitUntilCompleted();

    // Output to image
    cout << "Shader has completed render pass! Writing image now" << endl;
    int bytesPerRow = m_ImageProperties.imgWidth * pixelProperties.bytesPerPixel;
    int numBytes = bytesPerRow * m_ImageProperties.imgHeight;
    auto textureData = (float *) malloc(numBytes);
    MTL::Region mtlRegion = MTL::Region::Make2D(0, 0, m_ImageProperties.imgWidth, m_ImageProperties.imgHeight);
    texture->getBytes(textureData, bytesPerRow, numBytes, mtlRegion, 0, 0);

    ofstream image("../renders/image.ppm");
    if (!image.is_open())
    {
        cout << "Couldn't open image to write to. All that work for nothing..." << endl;
        return;
    }
    image << "P3\n" << m_ImageProperties.imgWidth << ' ' << m_ImageProperties.imgHeight << "\n255\n";
    for (int i = 0; i < numBytes / pixelProperties.componentsPerPixel; i += 4)
    {
        int red = static_cast<int>(textureData[i] * 255);
        int green = static_cast<int>(textureData[i + 1] * 255);
        int blue = static_cast<int>(textureData[i + 2] * 255);
        int alpha = static_cast<int>(textureData[i + 3] * 255);

        image << red << ' ' << green << ' ' << blue << endl;
    }
    free(textureData);

    // Release Cocoa objects
    metalLibFilePath->release();
    kernelFunctionName->release();
    mtlDevice->release();
    commandQueue->release();
    mtlLibrary->release();
    rayTracingFunction->release();
    rtPipelineState->release();
    commandBuffer->release();
    encoder->release();
    texture->release();

    cout << "Render complete!";
}
