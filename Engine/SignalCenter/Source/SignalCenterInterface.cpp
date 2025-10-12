//
// Created by 30632 on 2025/10/8.
//

#include "SignalCenter/SignalCenterInterface.h"

using namespace std;
using namespace WorldEngine;

std::shared_ptr<SignalCenter> WorldEngine::CreateSignalCenter()
{
    return make_shared<SignalCenter>();
}

std::shared_ptr<SignalCenter> WorldEngine::GetSignalCenter()
{
    return SignalCenter::Instance();
}