//
// Created by 30632 on 2025/10/12.
//

#include "InputHandler.h"

#include <iostream>

#include "SignalCenter/SignalCenterInterface.h"

using namespace std;
using namespace WorldEngine;

static void onMouseLeftDown(float x, float y, int mods)
{
    std::cout << "onMouseLeftDown: " << x << ", " << y << " mods:" << mods << std::endl;
}

static void onMouseLeftUp(float x, float y, int mods)
{
    std::cout << "onMouseLeftUp: " << x << ", " << y << " mods:" << mods << std::endl;
}

static void onMouseRightDown(float x, float y, int mods)
{
    std::cout << "onMouseRightDown: " << x << ", " << y << " mods:" << mods << std::endl;
}

static void onMouseRightUp(float x, float y, int mods)
{
    std::cout << "onMouseRightUp: " << x << ", " << y << " mods:" << mods << std::endl;
}

void InputHandler::init()
{
    GetSignalCenter()->connect(SignalId(SIGNAL_MOUSE_LEFT_DOWN), onMouseLeftDown);
    GetSignalCenter()->connect(SignalId(SIGNAL_MOUSE_LEFT_UP), onMouseLeftUp);
    GetSignalCenter()->connect(SignalId(SIGNAL_MOUSE_RIGHT_DOWN), onMouseRightDown);
    GetSignalCenter()->connect(SignalId(SIGNAL_MOUSE_RIGHT_UP), onMouseRightUp);
}

void InputHandler::shutdown()
{
    GetSignalCenter()->disconnectAll();
}