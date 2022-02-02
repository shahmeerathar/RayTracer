#include <metal_stdlib>

using namespace metal;

struct Ray
{
    // TODO: Might need to make a class
    float3 origin;
    float3 direction;
} typedef Ray;

struct Scene
{
    // TODO: ??? absolutely not - needs a lot of work
    int temp;
};

float randomFloat()
{
    // TODO: IMPLEMENT THIS
    return 1.0;
}

Ray getRayFromCamera(int u, int v)
{
    // TODO: IMPLEMENT THIS
    Ray ray;
    ray.origin = float3(0.0);
    ray.direction = float3(0.0);
    return ray;
}

float3 colourRay(Ray ray, Scene scene, int depth)
{
    // TODO: IMPLEMENT THIS
    return float3(0.0);
}

kernel void rayTrace(texture2d<half, access::write>  renderTexture  [[texture(0)]],
                     constant int& imgWidth [[buffer(0)]],
                     constant int& imgHeight [[buffer(1)]],
                     constant int& samplesPerPixel [[buffer(2)]],
                     uint2 index [[thread_position_in_grid]])
{
    int x = index[0];
    int y = index[1];
    
    float3 pixel = float3(0.0);
    for (int sampleNumber = 0; sampleNumber < samplesPerPixel; sampleNumber++)
    {
        float u = x + randomFloat() / imgWidth;
        float v = y + randomFloat() / imgHeight;
        
        Ray ray = getRayFromCamera(u, v);
        Scene scene;
        scene.temp = 1;
        pixel += colourRay(ray, scene, 1);
    }
    
    pixel *= 1.0 / samplesPerPixel;
    renderTexture.write(half4(pixel[0], pixel[1], pixel[2], 1.0), index);
    
    
    // TEST
    half red = 1.0 * index[0] / imgWidth;
    half green = 0.3;
    half blue = 0.5 * index[1] / imgHeight;
    half alpha = 1.0;
    renderTexture.write(half4(red, green, blue, alpha), index);
}
