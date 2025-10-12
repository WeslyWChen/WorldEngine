//
// Created by 30632 on 2025/10/10.
//

#include "GameEngine/GameEngineInterface.h"

#include "GameEngine.h"

using namespace std;
using namespace WorldEngine;

std::shared_ptr<IGameEngine> WorldEngine::GetGameEngine()
{
    return GameEngine::Instance();
}