//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_IWINDOWLAYER_H
#define WORLDENGINE_IWINDOWLAYER_H

#include <memory>

#include "IPainter.h"

namespace WorldEngine
{
    struct IWindowLayer {
        virtual ~IWindowLayer() = default;
        virtual void draw(std::shared_ptr<IPainter> painter) = 0;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_IWINDOWLAYER_H
