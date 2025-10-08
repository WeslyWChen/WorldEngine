//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_IRENDEROBJECT_H
#define WORLDENGINE_IRENDEROBJECT_H

namespace WorldEngine
{
    struct IRenderObject {
        virtual ~IRenderObject() = default;

        virtual void init() = 0;
        virtual void shutdown() = 0;
        virtual void run() = 0;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_IRENDEROBJECT_H
