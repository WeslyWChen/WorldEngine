//
// Created by 30632 on 2025/10/12.
//

#ifndef WORLDENGINE_SIGNALWRAPPER_H
#define WORLDENGINE_SIGNALWRAPPER_H

#include <any>
#include <vector>

#include "ISignalDefine.h"
#include "SlotWrapper.h"

namespace WorldEngine
{
    struct ISignalWrapper {
        virtual ~ISignalWrapper() = default;

        virtual bool isConnected(const SlotId& slotId) const = 0;

        virtual SlotId connect(std::shared_ptr<ISlotWrapper> slot) = 0;
        virtual void disconnect(const SlotId& slotId) = 0;
        virtual void disconnectAll() = 0;

        virtual void emit(const std::vector<std::any>& args) = 0;
    };

    template <typename... Args>
    class SignalWrapper final : public ISignalWrapper {
    public:
        SignalWrapper() = default;
        ~SignalWrapper() override = default;
        SignalWrapper(const SignalWrapper&) = delete;
        SignalWrapper& operator=(const SignalWrapper&) = delete;
        SignalWrapper(SignalWrapper&&) = delete;
        SignalWrapper& operator=(SignalWrapper&&) = delete;

    public:  // ISignalWrapper
        bool isConnected(const SlotId& slotId) const override
        {
            std::lock_guard<decltype(mMutex)> guard(mMutex);
            return mSlots.contains(slotId);
        }
        SlotId connect(std::shared_ptr<ISlotWrapper> slot) override
        {
            if (!slot)
                return 0;
            if (slot->getTypeIndex() != typeid(SlotFunction<Args...>))
                return 0;

            std::lock_guard<decltype(mMutex)> guard(mMutex);
            return mSlots.emplace(mNextSlotId++, slot).first->first;
        }
        void disconnect(const SlotId& slotId) override
        {
            std::lock_guard<decltype(mMutex)> guard(mMutex);
            mSlots.erase(slotId);
        }
        void disconnectAll() override
        {
            std::lock_guard<decltype(mMutex)> guard(mMutex);
            mSlots.clear();
        }
        void emit(const std::vector<std::any>& args) override
        {
            std::lock_guard<decltype(mMutex)> guard(mMutex);

            auto it = mSlots.begin();
            while (it != mSlots.end()) {
                auto& slot = it->second;
                if (!slot) {
                    it = mSlots.erase(it);
                    continue;
                }
                slot->call(args);
                ++it;
            }
        }

    private:
        mutable std::mutex mMutex;
        std::map<SlotId, std::shared_ptr<ISlotWrapper>> mSlots;
        SlotId mNextSlotId = 1;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_SIGNALWRAPPER_H
