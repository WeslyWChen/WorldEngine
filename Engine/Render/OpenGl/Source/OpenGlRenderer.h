//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_OPENGLRENDERER_H
#define WORLDENGINE_OPENGLRENDERER_H

#include "Render/IRenderer.h"

namespace WorldEngine
{
    class OpenGlRenderer final : public IRenderer {
    public:
        OpenGlRenderer() = default;
        ~OpenGlRenderer() override = default;
        OpenGlRenderer(const OpenGlRenderer&) = delete;
        OpenGlRenderer& operator=(const OpenGlRenderer&) = delete;
        OpenGlRenderer(OpenGlRenderer&&) = delete;
        OpenGlRenderer& operator=(OpenGlRenderer&&) = delete;

    public:  // IRenderer
        void init() override;
        void shutdown() override;
        void run() override;
        void addRenderObject(std::shared_ptr<IRenderObject> renderObject) override;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_OPENGLRENDERER_H
