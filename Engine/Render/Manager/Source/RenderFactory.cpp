//
// Created by 30632 on 2025/10/12.
//

#include "RenderFactory.h"

#include "OpenGL/OpenGLRenderer.h"

using namespace std;
using namespace WorldEngine;

std::shared_ptr<IRenderer> RenderFactory::CreateRender(RenderBackend backend)
{
    switch (backend) {
        case RenderBackend::OpenGL:
            return make_shared<OpenGLRenderer>();
        default:
            return nullptr;
    }
}