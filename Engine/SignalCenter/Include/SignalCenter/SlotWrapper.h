//
// Created by 30632 on 2025/10/12.
//

#ifndef WORLDENGINE_SLOTWRAPPER_H
#define WORLDENGINE_SLOTWRAPPER_H

#include <any>
#include <typeindex>
#include <vector>

#include "ISignalDefine.h"

namespace WorldEngine
{
    struct ISlotWrapper {
        virtual ~ISlotWrapper() = default;
        virtual std::type_index getTypeIndex() const = 0;
        virtual void call(const std::vector<std::any>& args) = 0;
    };

    template <typename... Args>
    class SlotWrapper final : public ISlotWrapper {
    public:
        explicit SlotWrapper(const SlotFunction<Args...>& slot) : mSlot(slot) {}
        ~SlotWrapper() override = default;
        SlotWrapper(const SlotWrapper&) = delete;
        SlotWrapper& operator=(const SlotWrapper&) = delete;
        SlotWrapper(SlotWrapper&&) = delete;
        SlotWrapper& operator=(SlotWrapper&&) = delete;

    public:  // ISlotWrapper
        std::type_index getTypeIndex() const override { return typeid(SlotFunction<Args...>); }
        void call(const std::vector<std::any>& args) override
        {
            if (args.size() != sizeof...(Args))
                return;

            callImpl(args, std::make_index_sequence<sizeof...(Args)>());
        }

    private:
        template <std::size_t... I>
        void callImpl(const std::vector<std::any>& args, std::index_sequence<I...>)
        {
            if (!mSlot)
                return;
            mSlot(std::any_cast<std::decay_t<Args>>(args[I])...);
        }

    private:
        SlotFunction<Args...> mSlot;
    };

}  // namespace WorldEngine

#endif  // WORLDENGINE_SLOTWRAPPER_H
