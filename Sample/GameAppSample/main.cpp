//
// Created by 30632 on 2025/10/10.
//

#include "App/GameApp.h"
#include "InputHandler.h"
#include "SignalCenter/SignalCenterInterface.h"

using namespace std;
using namespace WorldEngine;

int main(int argc, char** argv)
{
    InputHandler inputHandler;
    inputHandler.init();

    GameApp app(argc, argv);
    app.run();

    inputHandler.shutdown();

    return 0;
}