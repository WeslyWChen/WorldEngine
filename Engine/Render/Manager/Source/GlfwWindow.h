//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_GLFWWINDOW_H
#define WORLDENGINE_GLFWWINDOW_H

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
        void init(RenderBackend type, std::string title, int width, int height) override;
        void unInit() override;
        void addLayer(std::shared_ptr<IWindowLayer> windowLayer) override;
        void run() override;

    private:
        void inputHandle();

    private:
        std::string mTitle {};
        int mWidth {};
        int mHeight {};
    };
}  // namespace WorldEngine

#endif  // WORLDENGINE_GLFWWINDOW_H
