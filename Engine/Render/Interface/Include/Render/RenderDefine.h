//
// Created by 30632 on 2025/10/9.
//

#ifndef WORLDENGINE_RENDERDEFINE_H
#define WORLDENGINE_RENDERDEFINE_H

namespace WorldEngine
{
    enum class RenderBackend : std::uint8_t { OpenGL, Vulkan, DirectX11, DirectX12, Metal, WebGPU, Count };
}

#endif  // WORLDENGINE_RENDERDEFINE_H
