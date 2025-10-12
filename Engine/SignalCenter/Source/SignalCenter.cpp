//
// Created by 30632 on 2025/10/8.
//

#include "SignalCenter/SignalCenter.h"

#include <future>

using namespace std;
using namespace WorldEngine;

void SignalCenter::init()
{
    startupSignalThread();
}

void SignalCenter::shutdown()
{
    shutdownSignalThread();

    disconnectAll();
}

bool SignalCenter::isSignalExist(const SignalId& signalId) const
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);
    auto it = mSignals.find(signalId);
    if (it == mSignals.end())
        return false;
    if (!it->second)
        return false;

    return true;
}

bool SignalCenter::isConnected(const SignalId& signalId, const SlotId& slotId) const
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);
    auto it = mSignals.find(signalId);
    if (it == mSignals.end())
        return false;
    if (!it->second)
        return false;
    if (!it->second->isConnected(slotId))
        return false;
    return true;
}

void SignalCenter::disconnect(const SignalId& signalId, const SlotId& slotId)
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);

    auto it = mSignals.find(signalId);
    if (it == mSignals.end())
        return;
    if (!it->second)
        return;

    it->second->disconnect(slotId);
}

void SignalCenter::disconnectAll(const SignalId& signalId)
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);

    auto it = mSignals.find(signalId);
    if (it == mSignals.end())
        return;
    if (!it->second)
        return;

    it->second->disconnectAll();
}

void SignalCenter::disconnectAll()
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);

    mSignals.clear();
}

void SignalCenter::runMainThread()
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfMainThreadSignalQueue);
    for (auto& signalTask : mMainThreadSignalQueue) {
        if (!signalTask.callback)
            continue;
        signalTask.callback();
    }
    mMainThreadSignalQueue.clear();
}

void SignalCenter::startupSignalThread()
{
    if (mRunning && mSignalThread.valid())
        return;

    mRunning = true;
    mSignalThread = async([this] {
        while (mRunning) {
            unique_lock<decltype(mMutexOfSignalThread)> guard(mMutexOfSignalThread);
            mSignalThreadConditionV.wait(guard);
            for (const auto& signalTask : mSignalThreadSignalQueue) {
                if (!signalTask.callback)
                    continue;
                signalTask.callback();
            }
            mSignalThreadSignalQueue.clear();
        }
    });
}

void SignalCenter::shutdownSignalThread()
{
    mRunning = false;
    mSignalThreadConditionV.notify_all();
    if (mSignalThread.valid())
        mSignalThread.wait();
}
