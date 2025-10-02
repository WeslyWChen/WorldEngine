//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_MODULEMANAGER_H
#define WORLDENGINE_MODULEMANAGER_H

#include <stack>

#include "ModuleInterface.h"

namespace WorldEngine
{
    class ModuleManager final : public WorldEngine::IModuleManager {
    public:
        static ModuleManager& Instance();

    public:
        ModuleManager() = default;
        ~ModuleManager() override;
        ModuleManager(const ModuleManager&) = delete;
        ModuleManager& operator=(const ModuleManager&) = delete;
        ModuleManager(ModuleManager&&) = delete;
        ModuleManager& operator=(ModuleManager&&) = delete;

    public:  // IModuleManager
        void registerModule(std::shared_ptr<WorldEngine::IModule> module) override;

    private:
        std::stack<std::shared_ptr<WorldEngine::IModule>> mModules {};
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_MODULEMANAGER_H
