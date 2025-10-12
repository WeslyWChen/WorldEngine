//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_SIGNALCENTER_H
#define WORLDENGINE_SIGNALCENTER_H

#include <any>
#include <condition_variable>
#include <future>
#include <map>
#include <shared_mutex>
#include <thread>
#include <unordered_map>
#include <vector>

#include "Module/ModuleInterface.h"
#include "SignalCenterApi.h"
#include "SignalWrapper.h"
#include "SlotWrapper.h"

namespace WorldEngine
{
    class WE_SIGNALCENTER_API SignalCenter : public IModule {
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

    public:
        bool isSignalExist(const SignalId& signalId) const;
        bool isConnected(const SignalId& signalId, const SlotId& slotId) const;
        void disconnect(const SignalId& signalId, const SlotId& slotId);
        void disconnectAll(const SignalId& signalId);
        void disconnectAll();
        void runMainThread();
        void startupSignalThread();
        void shutdownSignalThread();

    public:
        template <typename... Args>
        bool registerSignal(const SignalId& signalId)
        {
            std::lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);
            if (mSignals.contains(signalId))
                return false;

            return mSignals.emplace(signalId, std::make_shared<SignalWrapper<Args...>>()).second;
        }

        template <typename... Args>
        SlotId connect(const SignalId& signalId, const SlotFunction<Args...>& slot)
        {
            std::lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);
            auto it = mSignals.find(signalId);
            if (it == mSignals.end())
                it = mSignals.emplace(signalId, std::make_shared<SignalWrapper<Args...>>()).first;

            auto slotWrapper = std::make_shared<SlotWrapper<Args...>>(slot);
            return it->second->connect(std::move(slotWrapper));
        }

        template <typename T, typename... Args>
        SlotId connect(const SignalId& signalId, T* obj, void (T::*func)(Args...))
        {
            return connect<Args...>(signalId, [obj, func](Args... args) { (obj->*func)(std::forward<Args>(args)...); });
        }

        template <typename... Args>
        SlotId connect(const SignalId& signalId, void (*func)(Args...))
        {
            SlotFunction<Args...> slot = [func](Args... args) { func(std::forward<Args>(args)...); };
            return connect(signalId, slot);
        }

        SlotId connect(const SignalId& signalId, const std::function<void()>& slot) { return connect<>(signalId, slot); }

        template <typename... Args>
        void emitSignal(const SignalId& signalId, Args&&... args)
        {
            std::vector<std::any> argsList;
            argsList.reserve(sizeof...(Args));
            (argsList.emplace_back(std::forward<Args>(args)), ...);

            std::lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignals);
            if (auto signal = mSignals.find(signalId); signal != mSignals.end())
                signal->second->emit(argsList);
        }

        template <typename... Args>
        void emitSignalMainThread(const SignalId& signalId, Args&&... args)
        {
            std::lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfMainThreadSignalQueue);

            SignalTask task;
            task.signalId = signalId;
            task.callback = [this, signalId, args...]() { emitSignal(signalId, args...); };
            mMainThreadSignalQueue.push_back(std::move(task));
        }

        template <typename... Args>
        void emitSignalSignalThread(const SignalId& signalId, Args&&... args)
        {
            std::lock_guard<decltype(mMutexOfSignals)> guard(mMutexOfSignalThread);

            SignalTask task;
            task.signalId = signalId;
            task.callback = [this, signalId, args...]() { emitSignal(signalId, args...); };
            mSignalThreadSignalQueue.push_back(std::move(task));
        }

    private:
        struct SignalTask {
            SignalId signalId;
            std::function<void()> callback;
        };

        mutable std::mutex mMutexOfSignals;
        std::unordered_map<SignalId, std::shared_ptr<ISignalWrapper>> mSignals;

        // main thread
        mutable std::mutex mMutexOfMainThreadSignalQueue;
        std::vector<SignalTask> mMainThreadSignalQueue;

        // signal thread
        mutable std::mutex mMutexOfSignalThread;
        std::vector<SignalTask> mSignalThreadSignalQueue;
        std::future<void> mSignalThread;
        std::atomic_bool mRunning = true;
        std::condition_variable mSignalThreadConditionV;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_SIGNALCENTER_H
