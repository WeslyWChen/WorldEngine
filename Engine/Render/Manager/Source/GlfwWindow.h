//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_GLFWWINDOW_H
#define WORLDENGINE_GLFWWINDOW_H

#include <condition_variable>
#include <future>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Render/IRenderer.h"
#include "Render/IWindow.h"

namespace WorldEngine
{
    class GlfwWindow final : public IWindow {
    public:
        GlfwWindow() = default;
        ~GlfwWindow() override = default;
        GlfwWindow(const GlfwWindow&) = delete;
        GlfwWindow& operator=(const GlfwWindow&) = delete;
        GlfwWindow(GlfwWindow&&) = delete;
        GlfwWindow& operator=(GlfwWindow&&) = delete;

    public:  // IWindow
        void* getWindow() const override;
        void init(RenderBackend type, std::string title, int width, int height) override;
        void run(std::shared_ptr<ITicker> ticker) override;
        void unInit() override;
        void addLayer(std::shared_ptr<IWindowLayer> windowLayer) override;

    public:
        void mainTick(const std::shared_ptr<ITicker>& ticker);
        void commitRenderCommand();
        void renderLoop();

    private:
        RenderBackend mRenderBackend = RenderBackend::OpenGL;
        std::string mTitle {};
        int mWidth {};
        int mHeight {};

        GLFWwindow* mWindow = nullptr;

        std::atomic_bool mRunning = false;
        std::future<void> mRenderFuture;
        std::mutex mRenderMutex;
        std::condition_variable mRenderCond;
        std::shared_ptr<IRenderer> mRenderer = nullptr;
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_GLFWWINDOW_H
