#include <metal_stdlib>

using namespace metal;

kernel void rayTrace(texture2d<half, access::write>  renderTexture  [[texture(0)]],
                     uint2 index [[thread_position_in_grid]])
{
    renderTexture.write(half4(1.0 * index[0] / 1200, 0.3, 0.5 * index[1] / 1200, 1.0), index);
}
