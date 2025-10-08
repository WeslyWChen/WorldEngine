//
// Created by 30632 on 2025/10/8.
//

#include "SignalCenter.h"

#include <cassert>
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
    if (it->second.empty())
        return false;
    return true;
}

bool SignalCenter::isConnected(const SignalId& signalId, const SlotId& slotId) const
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);
    auto it = mSignals.find(signalId);
    if (it == mSignals.end())
        return false;
    if (!it->second.contains(slotId))
        return false;
    return true;
}

void SignalCenter::emitSignal(const SignalId& signalId, SignalTrigger type)
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);
    auto it = mSignals.find(signalId);
    if (it == mSignals.end())
        return;

    switch (type) {
        case SignalTrigger::MAIN_THREAD: {
            mMainThreadSignalQueue.push_back(signalId);
            break;
        }
        case SignalTrigger::SIGNAL_THREAD: {
            lock_guard<decltype(mMutexOfSignalThread)> guardOfSignalThread(mMutexOfSignalThread);
            mSignalThreadSignalQueue.push_back(signalId);
            mSignalThreadConditionV.notify_one();
            break;
        }
        default: {
            for (auto& slot : it->second)
                slot.second();
            break;
        }
    }
}

SlotId SignalCenter::connect(const SignalId& signalId, const SlotFunction<>& slot)
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);

    SlotId slotId = mSlotIdCount++;
    assert(slotId != 0);  // do not consider so much slots

    mSignals[signalId].emplace(slotId, slot);
    return slotId;
}

void SignalCenter::disconnect(const SignalId& signalId, const SlotId& slotId)
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);

    auto it = mSignals.find(signalId);
    if (it == mSignals.end())
        return;

    it->second.erase(slotId);

    if (it->second.empty())
        mSignals.erase(it);
}

void SignalCenter::disconnectAll(const SignalId& signalId)
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);

    auto it = mSignals.find(signalId);
    if (it == mSignals.end())
        return;

    mSignals.erase(it);
}

void SignalCenter::disconnectAll()
{
    lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);

    mSignals.clear();
}

void SignalCenter::runMainThread()
{
    for (auto& signalId : mMainThreadSignalQueue)
        emitSignal(signalId);
}

void SignalCenter::startupSignalThread()
{
    if (mRunning && mSignalThread.valid())
        return;

    mRunning = true;
    mSignalThread = std::async([this] {
        while (mRunning) {
            unique_lock<decltype(mMutexOfSignalThread)> guard(mMutexOfSignalThread);
            mSignalThreadConditionV.wait(guard);
            for (const auto& signalId : mSignalThreadSignalQueue)
                emitSignal(signalId);
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
