//
// Created by 30632 on 2025/10/8.
//

#include "RenderOpenGlInterface.h"

#include "OpenGlRenderer.h"

using namespace std;
using namespace WorldEngine;

std::shared_ptr<WorldEngine::IRenderer> WorldEngine::CreateOpenGlRenderer()
{
    return make_shared<OpenGlRenderer>();
}