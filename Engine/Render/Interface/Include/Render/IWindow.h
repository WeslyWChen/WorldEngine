//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_IWINDOW_H
#define WORLDENGINE_IWINDOW_H

#include <string>

#include "IWindowLayer.h"
#include "RenderDefine.h"
#include "WorldEngine/ITicker.h"

namespace WorldEngine
{
    struct IWindow {
        virtual ~IWindow() = default;

        virtual void* getWindow() const = 0;

        virtual void init(RenderBackend type, std::string title, int width, int height) = 0;
        virtual void run(std::shared_ptr<ITicker> ticker) = 0;
        virtual void unInit() = 0;
        virtual void addLayer(std::shared_ptr<IWindowLayer> windowLayer) = 0;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_IWINDOW_H
