//
// Created by 30632 on 2025/10/10.
//

#ifndef WORLDENGINE_GAMEENGINEINTERFACE_H
#define WORLDENGINE_GAMEENGINEINTERFACE_H

#include <memory>

#include "GameEngineApi.h"
#include "WorldEngine/ITicker.h"

namespace WorldEngine
{
    struct IGameEngine : public ITicker {};

    WE_GAMEENGINE_API std::shared_ptr<IGameEngine> GetGameEngine();

}  // namespace WorldEngine

#endif  // WORLDENGINE_GAMEENGINEINTERFACE_H
