//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_MODULEINTERFACE_H
#define WORLDENGINE_MODULEINTERFACE_H

#include <memory>

#include "ModuleApi.h"

namespace WorldEngine
{
    struct IModule {
        virtual ~IModule() = default;

        /**
         * @brief initialize the module
         */
        virtual void init() = 0;

        /**
         * @brief shutdown the module
         */
        virtual void shutdown() = 0;
    };

    struct IModuleManager {
        virtual ~IModuleManager() = default;

        /**
         * @brief register a module, which is automatically released at the end of the program according to the order of the stacks.
         * @param module the module to be registered
         */
        virtual void registerModule(std::shared_ptr<IModule> module) = 0;
    };

    WE_MODULE_API IModuleManager& GetModuleManager();

}  // namespace WorldEngine

#define DEFINE_MODULE_INSTANCE(className)                                                \
    static std::shared_ptr<className> Instance()                                         \
    {                                                                                    \
        struct className##Impl : public className {};                                    \
        struct className##ImplImpl {                                                     \
            std::shared_ptr<className##Impl> impl = std::make_shared<className##Impl>(); \
            className##ImplImpl()                                                        \
            {                                                                            \
                WorldEngine::GetModuleManager().registerModule(impl);                    \
            }                                                                            \
            ~className##ImplImpl() = default;                                            \
        };                                                                               \
        static className##ImplImpl instance;                                             \
        return instance.impl;                                                            \
    }

#endif  // WORLDENGINE_MODULEINTERFACE_H
