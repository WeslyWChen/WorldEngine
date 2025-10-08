//
// Created by 30632 on 2025/10/7.
//

#include "ModuleManager.h"

using namespace std;
using namespace WorldEngine;

ModuleManager& ModuleManager::Instance()
{
    static ModuleManager instance;
    return instance;
}

ModuleManager::~ModuleManager()
{
    while (!mModules.empty()) {
        if (auto module = mModules.top())
            module->shutdown();
        mModules.pop();
    }
}

void ModuleManager::registerModule(std::shared_ptr<WorldEngine::IModule> module)
{
    if (!module)
        return;

    module->init();
    mModules.push(module);
}