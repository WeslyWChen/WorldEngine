//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_APP_H
#define WORLDENGINE_APP_H

#include "AppApi.h"

namespace WorldEngine
{
    class WEAPP_API App {
    protected:
        App(int argc, char** argv);
        virtual ~App() = default;
        App(const App&) = delete;
        App& operator=(const App&) = delete;
        App(App&&) = delete;
        App& operator=(App&&) = delete;

    public:
        void run();

    protected:
        virtual void onRun() = 0;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_APP_H
