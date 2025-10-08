//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_WINDOWAPP_H
#define WORLDENGINE_WINDOWAPP_H

#include <memory>
#include <string>

#include "App.h"
#include "AppApi.h"

namespace WorldEngine
{
    class WEAPP_API WindowApp : public App {
    public:
        WindowApp(int argc, char** argv);
        ~WindowApp() override;
        WindowApp(const WindowApp&) = delete;
        WindowApp& operator=(const WindowApp&) = delete;
        WindowApp(WindowApp&&) = delete;
        WindowApp& operator=(WindowApp&&) = delete;

    protected:  // App
        void onRun() override;

    public:
        void setTitle(const std::string& title);
        void setSize(int width, int height);

    private:
        struct WinAppImpl;
        std::unique_ptr<WinAppImpl> mImpl;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_WINDOWAPP_H
