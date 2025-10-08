//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_RENDEROPENGLINTERFACE_H
#define WORLDENGINE_RENDEROPENGLINTERFACE_H

#include "Render/IRenderer.h"
#include "Render/RenderOpenGlApi.h"

namespace WorldEngine
{
    WERENDEROPENGL_API std::shared_ptr<IRenderer> CreateOpenGlRenderer();
}  // namespace WorldEngine

#endif  // WORLDENGINE_RENDEROPENGLINTERFACE_H
