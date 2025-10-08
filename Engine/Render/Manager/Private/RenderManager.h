//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_RENDERMANAGER_H
#define WORLDENGINE_RENDERMANAGER_H

#include "ModuleInterface.h"
#include "RenderManagerInterface.h"

namespace WorldEngine
{
    class RenderManager : public IModule, public IRenderManager {
    public:
        DEFINE_MODULE_INSTANCE(RenderManager)

    private:
        RenderManager() = default;
        ~RenderManager() override = default;
        RenderManager(const RenderManager&) = delete;
        RenderManager& operator=(const RenderManager&) = delete;
        RenderManager(RenderManager&&) = delete;
        RenderManager& operator=(RenderManager&&) = delete;

    public:
        void init() override;
        void shutdown() override;

    public:  // IRenderManager
        std::shared_ptr<IWindow> createWindow() override;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_RENDERMANAGER_H
