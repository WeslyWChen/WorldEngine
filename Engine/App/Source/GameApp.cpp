//
// Created by 30632 on 2025/10/10.
//

#include "App/GameApp.h"

#include "GameEngine/GameEngineInterface.h"
#include "Render/IWindow.h"
#include "Render/RenderManagerInterface.h"

using namespace std;
using namespace WorldEngine;

GameApp::GameApp(int argc, char** argv) : WindowApp(argc, argv) {}

GameApp::~GameApp() = default;

void GameApp::onRun()
{
    auto window = GetRenderManager().createWindow();
    if (!window)
        return;

    window->init(RenderBackend::OpenGL, getTitle(), getWidth(), getHeight());
    window->run(GetGameEngine());
    window->unInit();
}