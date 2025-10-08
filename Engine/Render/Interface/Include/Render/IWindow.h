//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_IWINDOW_H
#define WORLDENGINE_IWINDOW_H

#include <cstdint>
#include <string>

#include "IWindowLayer.h"

namespace WorldEngine
{
    enum class WindowType : std::uint8_t {
        WINDOW_TYPE_WIN32,
        WINDOW_TYPE_GLFW,
        WINDOW_TYPE_SDL,
        WINDOW_TYPE_VULKAN,
        WINDOW_TYPE_DX12,
        WINDOW_TYPE_DX11,
        WINDOW_TYPE_METAL,
        WINDOW_TYPE_OPENGL,
    };

    struct IWindow {
        virtual ~IWindow() = default;
        virtual void init(WindowType type, std::string title, int width, int height) = 0;
        virtual void unInit() = 0;
        virtual void addLayer(std::shared_ptr<IWindowLayer> windowLayer) = 0;
        virtual void run() = 0;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_IWINDOW_H
