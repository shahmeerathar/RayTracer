#include <metal_stdlib>

using namespace metal;

kernel void rayTrace(texture2d<half, access::write>  renderTexture  [[texture(0)]],
                     uint2 index [[thread_position_in_grid]])
{
    renderTexture.write(half4(1.0, 0.5, 0.6, 1.0), index);
}
