//
// Created by 30632 on 2025/10/7.
//

#include "RenderManager.h"

#include "GlfwWindow.h"

using namespace std;
using namespace WorldEngine;

void RenderManager::init() {}

void RenderManager::shutdown() {}

std::shared_ptr<IWindow> RenderManager::createWindow()
{
    return make_shared<GlfwWindow>();
}