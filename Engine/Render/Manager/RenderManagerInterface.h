//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_RENDERMANAGERINTERFACE_H
#define WORLDENGINE_RENDERMANAGERINTERFACE_H

#include "IWindow.h"
#include "RenderManagerApi.h"

namespace WorldEngine
{
    struct IRenderManager {
        virtual ~IRenderManager() = default;

        virtual std::shared_ptr<IWindow> createWindow() = 0;
    };

    WERENDERMANAGER_API IRenderManager& GetRenderManager();

}  // namespace WorldEngine

#endif  // WORLDENGINE_RENDERMANAGERINTERFACE_H
