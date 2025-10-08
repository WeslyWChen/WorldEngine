//
// Created by 30632 on 2025/10/8.
//

#include "RenderManagerInterface.h"

#include "RenderManager.h"

using namespace std;
using namespace WorldEngine;

WorldEngine::IRenderManager& WorldEngine::GetRenderManager()
{
    return *RenderManager::Instance();
}