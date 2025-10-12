//
// Created by 30632 on 2025/10/12.
//

#ifndef WORLDENGINE_OPENGLRENDERER_H
#define WORLDENGINE_OPENGLRENDERER_H

#include <future>

#include "Render/IRenderer.h"

namespace WorldEngine
{
    class OpenGLRenderer final : public IRenderer {
    public:
        OpenGLRenderer() = default;
        ~OpenGLRenderer() override = default;
        OpenGLRenderer(const OpenGLRenderer&) = delete;
        OpenGLRenderer& operator=(const OpenGLRenderer&) = delete;
        OpenGLRenderer(OpenGLRenderer&&) = delete;
        OpenGLRenderer& operator=(OpenGLRenderer&&) = delete;

    public:  // IRenderer
        void init() override;
        void shutdown() override;
        void addRenderObject(std::shared_ptr<IRenderObject> renderObject) override;
        void render(IWindow* window) override;

    private:
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_OPENGLRENDERER_H
