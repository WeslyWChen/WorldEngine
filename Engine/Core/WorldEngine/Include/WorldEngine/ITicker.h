//
// Created by 30632 on 2025/10/12.
//

#ifndef WORLDENGINE_ITICKER_H
#define WORLDENGINE_ITICKER_H

namespace WorldEngine
{
    struct ITicker {
        virtual ~ITicker() = default;

        virtual void onInput() = 0;
        virtual void onTick() = 0;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_ITICKER_H
