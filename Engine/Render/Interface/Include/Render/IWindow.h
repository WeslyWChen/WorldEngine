//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_IWINDOW_H
#define WORLDENGINE_IWINDOW_H

#include <cstdint>
#include <string>

#include "IWindowLayer.h"
#include "RenderDefine.h"

namespace WorldEngine
{
    struct IWindow {
        virtual ~IWindow() = default;
        virtual void init(RenderBackend type, std::string title, int width, int height) = 0;
        virtual void unInit() = 0;
        virtual void addLayer(std::shared_ptr<IWindowLayer> windowLayer) = 0;
        virtual void run() = 0;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_IWINDOW_H
