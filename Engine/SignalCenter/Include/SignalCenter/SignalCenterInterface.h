//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_SIGNALCENTERINTERFACE_H
#define WORLDENGINE_SIGNALCENTERINTERFACE_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

#include "SignalCenterApi.h"

namespace WorldEngine
{
    using SignalId = std::string;
    using SlotId = std::uint64_t;

    template <typename... Args>
    using SlotFunction = std::function<void(Args...)>;

    enum class SignalTrigger { IMMEDIATE, MAIN_THREAD, SIGNAL_THREAD };

    struct ISignalCenter {
        virtual ~ISignalCenter() = default;

        virtual bool isSignalExist(const SignalId& signalId) const = 0;
        virtual bool isConnected(const SignalId& signalId, const SlotId& slotId) const = 0;

        virtual void emitSignal(const SignalId& signalId, SignalTrigger type = SignalTrigger::IMMEDIATE) = 0;
        virtual SlotId connect(const SignalId& signalId, const SlotFunction<>& slot) = 0;
        virtual void disconnect(const SignalId& signalId, const SlotId& slotId) = 0;
        virtual void disconnectAll(const SignalId& signalId) = 0;
        virtual void disconnectAll() = 0;

        virtual void runMainThread() = 0;
        virtual void startupSignalThread() = 0;
        virtual void shutdownSignalThread() = 0;
    };

    /**
     * @brief create a signal center, provided for unit test code
     * @return a shared pointer to the signal center
     */
    WE_SIGNALCENTER_API std::shared_ptr<ISignalCenter> CreateSignalCenter();

    /**
     * @brief get the signal center of single instance
     * @return a reference to the signal center
     */
    WE_SIGNALCENTER_API ISignalCenter& GetSignalCenter();

}  // namespace WorldEngine

#endif  // WORLDENGINE_SIGNALCENTERINTERFACE_H
