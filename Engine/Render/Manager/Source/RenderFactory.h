//
// Created by 30632 on 2025/10/12.
//

#ifndef WORLDENGINE_RENDERFACTORY_H
#define WORLDENGINE_RENDERFACTORY_H

#include "Render/IRenderer.h"

namespace WorldEngine::RenderFactory
{
    std::shared_ptr<IRenderer> CreateRender(RenderBackend backend);
}

#endif  // WORLDENGINE_RENDERFACTORY_H
