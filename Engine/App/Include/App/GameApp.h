//
// Created by 30632 on 2025/10/10.
//

#ifndef WORLDENGINE_GAMEAPP_H
#define WORLDENGINE_GAMEAPP_H

#include "WindowApp.h"

namespace WorldEngine
{
    class WE_APP_API GameApp final : public WindowApp {
    public:
        GameApp(int argc, char** argv);
        ~GameApp() override;
        GameApp(const GameApp&) = delete;
        GameApp& operator=(const GameApp&) = delete;
        GameApp(GameApp&&) = delete;
        GameApp& operator=(GameApp&&) = delete;

    protected:  // WindowApp
        void onRun() override;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_GAMEAPP_H
