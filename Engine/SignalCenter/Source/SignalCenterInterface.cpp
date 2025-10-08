//
// Created by 30632 on 2025/10/8.
//

#include "SignalCenter/SignalCenterInterface.h"

#include "SignalCenter.h"

using namespace std;
using namespace WorldEngine;

std::shared_ptr<ISignalCenter> WorldEngine::CreateSignalCenter()
{
    return make_shared<SignalCenter>();
}

ISignalCenter& WorldEngine::GetSignalCenter()
{
    return *SignalCenter::Instance();
}