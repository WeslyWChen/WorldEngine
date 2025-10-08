//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_IPAINTER_H
#define WORLDENGINE_IPAINTER_H

#include "Math/Color.h"

namespace WorldEngine
{
    struct IPainter {
        virtual ~IPainter() = default;
        virtual void clear(Color color) = 0;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_IPAINTER_H
