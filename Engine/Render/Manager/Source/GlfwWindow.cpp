//
// Created by 30632 on 2025/10/8.
//

#include "GlfwWindow.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace std;
using namespace WorldEngine;

void GlfwWindow::init(RenderBackend type, std::string title, int width, int height)
{
    mTitle = title;
    mWidth = width;
    mHeight = height;
}

void GlfwWindow::unInit() {}

void GlfwWindow::addLayer(std::shared_ptr<IWindowLayer> windowLayer) {}

void GlfwWindow::run()
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

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        return;

    glViewport(0, 0, mWidth, mHeight);

    while (!glfwWindowShouldClose(window)) {
        // input handle
        inputHandle();

        // clear back buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void GlfwWindow::inputHandle() {}