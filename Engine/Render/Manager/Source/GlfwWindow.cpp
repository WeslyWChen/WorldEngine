//
// Created by 30632 on 2025/10/8.
//

#include "GlfwWindow.h"

#include "RenderFactory.h"
#include "SignalCenter/SignalCenterInterface.h"

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

    // NOLINTBEGIN
    glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        switch (action) {
            case GLFW_PRESS:
                GetSignalCenter()->emitSignal(SIGNAL_KEY_DOWN, key, mods);
                break;
            case GLFW_RELEASE:
                GetSignalCenter()->emitSignal(SIGNAL_KEY_UP, key, mods);
                break;
            case GLFW_REPEAT:
                GetSignalCenter()->emitSignal(SIGNAL_KEY_REPEAT, key, mods);
                break;
            default:
                break;
        }
    });
    glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
        double xpos = 0.0f;
        double ypos = 0.0f;
        glfwGetCursorPos(window, &xpos, &ypos);
        float fxpos = static_cast<float>(xpos);
        float fypos = static_cast<float>(ypos);
        switch (action) {
            case GLFW_PRESS: {
                switch (button) {
                    case GLFW_MOUSE_BUTTON_LEFT:
                        GetSignalCenter()->emitSignal(SIGNAL_MOUSE_LEFT_DOWN, fxpos, fypos, mods);
                        break;
                    case GLFW_MOUSE_BUTTON_RIGHT:
                        GetSignalCenter()->emitSignal(SIGNAL_MOUSE_RIGHT_DOWN, fxpos, fypos, mods);
                        break;
                    case GLFW_MOUSE_BUTTON_MIDDLE:
                        GetSignalCenter()->emitSignal(SIGNAL_MOUSE_MIDDLE_DOWN, fxpos, fypos, mods);
                        break;
                    default:
                        break;
                }
                break;
            }
            case GLFW_RELEASE: {
                switch (button) {
                    case GLFW_MOUSE_BUTTON_LEFT:
                        GetSignalCenter()->emitSignal(SIGNAL_MOUSE_LEFT_UP, fxpos, fypos, mods);
                        break;
                    case GLFW_MOUSE_BUTTON_RIGHT:
                        GetSignalCenter()->emitSignal(SIGNAL_MOUSE_RIGHT_UP, fxpos, fypos, mods);
                        break;
                    case GLFW_MOUSE_BUTTON_MIDDLE:
                        GetSignalCenter()->emitSignal(SIGNAL_MOUSE_MIDDLE_UP, fxpos, ypos, mods);
                        break;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
    });
    glfwSetCursorPosCallback(mWindow,
                             [](GLFWwindow* window, double xpos, double ypos) { GetSignalCenter()->emitSignal(SIGNAL_MOUSE_MOVE, xpos, ypos); });
    glfwSetScrollCallback(
            mWindow, [](GLFWwindow* window, double xoffset, double yoffset) { GetSignalCenter()->emitSignal(SIGNAL_MOUSE_WHEEL, xoffset, yoffset); });
    glfwSetWindowSizeCallback(mWindow,
                              [](GLFWwindow* window, int width, int height) { GetSignalCenter()->emitSignal(SIGNAL_WINDOW_RESIZE, width, height); });
    // NOLINTEND

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

void GlfwWindow::mainTick(const std::shared_ptr<ITicker>& ticker)
{
    if (!ticker)
        return;

    ticker->onTick();
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