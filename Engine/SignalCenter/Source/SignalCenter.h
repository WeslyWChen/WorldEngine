//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_SIGNALCENTER_H
#define WORLDENGINE_SIGNALCENTER_H

#include <future>
#include <map>
#include <shared_mutex>
#include <thread>
#include <unordered_map>

#include "Module/ModuleInterface.h"
#include "SignalCenter/SignalCenterInterface.h"

namespace WorldEngine
{
    class SignalCenter : public IModule, public ISignalCenter {
    public:
        DEFINE_MODULE_INSTANCE(SignalCenter)

    public:
        SignalCenter() = default;
        ~SignalCenter() override = default;
        SignalCenter(const SignalCenter&) = delete;
        SignalCenter& operator=(const SignalCenter&) = delete;
        SignalCenter(SignalCenter&&) = delete;
        SignalCenter& operator=(SignalCenter&&) = delete;

    public:  // IModule
        void init() override;
        void shutdown() override;

    public:  // ISignalCenter
        bool isSignalExist(const SignalId& signalId) const override;
        bool isConnected(const SignalId& signalId, const SlotId& slotId) const override;
        void emitSignal(const SignalId& signalId, SignalTrigger type = SignalTrigger::IMMEDIATE) override;
        SlotId connect(const SignalId& signalId, const SlotFunction<>& slot) override;
        void disconnect(const SignalId& signalId, const SlotId& slotId) override;
        void disconnectAll(const SignalId& signalId) override;
        void disconnectAll() override;
        void runMainThread() override;
        void startupSignalThread() override;
        void shutdownSignalThread() override;

    private:
        mutable std::shared_mutex mMutexOfSignals;
        std::uint64_t mSlotIdCount = 1;
        std::unordered_map<SignalId, std::map<SlotId, SlotFunction<>>> mSignals;

        std::vector<SignalId> mMainThreadSignalQueue;

        std::atomic_bool mRunning = true;
        std::future<void> mSignalThread;
        std::mutex mMutexOfSignalThread;
        std::condition_variable mSignalThreadConditionV;
        std::vector<SignalId> mSignalThreadSignalQueue;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_SIGNALCENTER_H
