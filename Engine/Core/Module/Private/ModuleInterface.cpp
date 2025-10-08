//
// Created by 30632 on 2025/10/7.
//

#include "ModuleInterface.h"

#include "ModuleManager.h"

using namespace std;
using namespace WorldEngine;

IModuleManager& WorldEngine::GetModuleManager()
{
    return ModuleManager::Instance();
}