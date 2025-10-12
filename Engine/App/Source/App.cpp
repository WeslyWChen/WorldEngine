//
// Created by 30632 on 2025/10/8.
//

#include "App/App.h"

#include "Module/ModuleInterface.h"

using namespace std;
using namespace WorldEngine;

App::App(int argc, char** argv) {}

void App::run()
{
    onRun();

    // sub thread should be stopped before main function returns
    GetModuleManager().shutdown();
}