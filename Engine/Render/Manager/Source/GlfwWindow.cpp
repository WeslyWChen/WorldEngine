//
// Created by 30632 on 2025/10/8.
//

#include "GlfwWindow.h"

#include "RenderFactory.h"

using namespace std;
using namespace WorldEngine;

void* GlfwWindow::getWindow() const
{
    return mWindow;
}

void GlfwWindow::init(RenderBackend type, std::string title, int width, int height)
{
    mRenderBackend = type;
    mTitle = title;
    mWidth = width;
    mHeight = height;
}

void GlfwWindow::run(std::shared_ptr<ITicker> ticker)
{
    if (!glfwInit())
        return;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    mWindow = window;

    mRenderer = RenderFactory::CreateRender(mRenderBackend);
    if (!mRenderer)
        return;

    mRunning = true;
    mRenderFuture = async(launch::async, [this]() { renderLoop(); });

    while (!glfwWindowShouldClose(mWindow)) {
        glfwPollEvents();

        mainTick(ticker);

        commitRenderCommand();
    }

    mRunning = false;
    mRenderCond.notify_all();
    if (mRenderFuture.valid())
        mRenderFuture.wait();

    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void GlfwWindow::unInit() {}

void GlfwWindow::addLayer(std::shared_ptr<IWindowLayer> windowLayer) {}

void GlfwWindow::mainTick(std::shared_ptr<ITicker> ticker)
{
    if (!ticker)
        return;
}

void GlfwWindow::commitRenderCommand() {}

void GlfwWindow::renderLoop()
{
    if (!mRenderer || !mWindow)
        return;

    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        return;

    int width = 0;
    int height = 0;
    glfwGetFramebufferSize(mWindow, &width, &height);
    glViewport(0, 0, width, height);

    mRenderer->init();

    while (mRunning) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        mRenderer->render(this);

        glfwSwapBuffers(mWindow);
    }

    mRenderer->shutdown();
}