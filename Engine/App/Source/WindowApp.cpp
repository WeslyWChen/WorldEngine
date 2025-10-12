//
// Created by 30632 on 2025/10/8.
//

#include "App/WindowApp.h"

#include "Render/RenderManagerInterface.h"

using namespace std;
using namespace WorldEngine;

struct WindowApp::WinAppImpl {
    std::string mTitle = "WindowApp";
    int mWidth = 800;
    int mHeight = 600;
};

WindowApp::WindowApp(int argc, char** argv) : App(argc, argv), mImpl(make_unique<WinAppImpl>()) {}

WindowApp::~WindowApp() = default;

void WindowApp::onRun()
{
    auto window = GetRenderManager().createWindow();
    if (!window)
        return;

    window->init(RenderBackend::OpenGL, mImpl->mTitle, mImpl->mWidth, mImpl->mHeight);
    window->run(nullptr);
    window->unInit();
}

std::string WindowApp::getTitle() const
{
    return mImpl->mTitle;
}

int WindowApp::getWidth() const
{
    return mImpl->mWidth;
}

int WindowApp::getHeight() const
{
    return mImpl->mHeight;
}

void WindowApp::setTitle(const std::string& title)
{
    mImpl->mTitle = title;
}

void WindowApp::setSize(int width, int height)
{
    mImpl->mWidth = width;
    mImpl->mHeight = height;
}