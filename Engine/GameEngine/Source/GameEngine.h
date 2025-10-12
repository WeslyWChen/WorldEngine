//
// Created by 30632 on 2025/10/10.
//

#ifndef WORLDENGINE_GAMEENGINE_H
#define WORLDENGINE_GAMEENGINE_H

#include "GameEngine/GameEngineInterface.h"
#include "Module/ModuleInterface.h"

namespace WorldEngine
{
    class GameEngine : public IModule, public IGameEngine {
    public:
        DEFINE_MODULE_INSTANCE(GameEngine)

    public:
        GameEngine() = default;
        ~GameEngine() override = default;
        GameEngine(const GameEngine&) = delete;
        GameEngine& operator=(const GameEngine&) = delete;
        GameEngine(GameEngine&&) = delete;
        GameEngine& operator=(GameEngine&&) = delete;

    public:  // IModule
        void init() override;
        void shutdown() override;

    public:  // IGameEngine
        void onInput() override;
        void onTick() override;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_GAMEENGINE_H
