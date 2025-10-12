//
// Created by 30632 on 2025/10/2.
//

#ifndef WORLDENGINE_WORLDENGINEMODULE_H
#define WORLDENGINE_WORLDENGINEMODULE_H

#include "Module/ModuleInterface.h"
#include "WorldEngine/WorldEngineApi.h"

namespace WorldEngine
{
    class WE_WORLDENGINE_API WorldEngineModule : public IModule {
    public:
        DEFINE_MODULE_INSTANCE(WorldEngineModule)
    public:
        WorldEngineModule() = default;
        ~WorldEngineModule() = default;
        WorldEngineModule(const WorldEngineModule&) = delete;
        WorldEngineModule& operator=(const WorldEngineModule&) = delete;
        WorldEngineModule(WorldEngineModule&&) = delete;
        WorldEngineModule& operator=(WorldEngineModule&&) = delete;

    public:  // IModule
        void init() override;
        void shutdown() override;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_WORLDENGINEMODULE_H
