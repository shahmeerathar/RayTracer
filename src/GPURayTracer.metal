#include <metal_stdlib>

using namespace metal;

kernel void rayTrace(texture2d<half, access::write>  renderTexture  [[texture(0)]],
                     constant int& imgWidth [[buffer(0)]],
                     constant int& imgHeight [[buffer(1)]],
                     constant int& samplesPerPixel [[buffer(2)]],
                     uint2 index [[thread_position_in_grid]])
{
    renderTexture.write(half4(1.0 * index[0] / imgWidth, 0.3, 0.5 * index[1] / imgHeight, 1.0), index);
}
