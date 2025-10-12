//
// Created by 30632 on 2025/10/12.
//

#include "OpenGLRenderer.h"

using namespace std;
using namespace WorldEngine;

void OpenGLRenderer::init() {}

void OpenGLRenderer::shutdown() {}

void OpenGLRenderer::addRenderObject(std::shared_ptr<IRenderObject> renderObject) {}

void OpenGLRenderer::render(IWindow* window)
{
    if (!window)
        return;

    // render handle
}