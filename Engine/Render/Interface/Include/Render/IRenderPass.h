//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_IRENDERPASS_H
#define WORLDENGINE_IRENDERPASS_H

#include <memory>

#include "IPainter.h"

namespace WorldEngine
{
    struct IRenderPass {
        virtual ~IRenderPass() = default;
        virtual void draw(std::shared_ptr<IPainter> painter) = 0;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_IRENDERPASS_H
