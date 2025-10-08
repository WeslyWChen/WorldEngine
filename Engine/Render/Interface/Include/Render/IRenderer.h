//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_IRENDERER_H
#define WORLDENGINE_IRENDERER_H

#include <memory>

#include "IRenderObject.h"

namespace WorldEngine
{
    struct IRenderer {
        virtual ~IRenderer() = default;

        virtual void init() = 0;
        virtual void shutdown() = 0;
        virtual void run() = 0;
        virtual void addRenderObject(std::shared_ptr<IRenderObject> renderObject) = 0;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_IRENDERER_H
