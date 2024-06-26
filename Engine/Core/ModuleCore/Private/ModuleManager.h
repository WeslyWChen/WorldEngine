//
// Created by WeslyChen on 2024/1/14.
//

#ifndef WORLDENGINE_MODULEMANAGER_H
#define WORLDENGINE_MODULEMANAGER_H

#include <stack>

#include "Core/BasicType/String.h"
#include "Core/Common/ClassMacro.h"
#include "ModuleCore.h"

class ModuleManager final : public ModuleCore::IManager
{
    SINGLETON_CLASS(ModuleManager)

public:
    void RegisterModule(ModuleCore::IModule* module) override;
    void UnregisterAll() override;

private:
    static String GetModuleName(ModuleCore::IModule* module);

private:
    std::stack<ModuleCore::IModule*> mModules;
};

#endif  // WORLDENGINE_MODULEMANAGER_H
