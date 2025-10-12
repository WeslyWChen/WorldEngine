//
// Created by 30632 on 2025/10/12.
//

#ifndef WORLDENGINE_ISIGNALDEFINE_H
#define WORLDENGINE_ISIGNALDEFINE_H

#include <cstdint>
#include <functional>
#include <string>

namespace WorldEngine
{
    using SignalId = std::string;
    using SlotId = std::uint64_t;

    template <typename... Args>
    using SlotFunction = std::function<void(Args...)>;

    constexpr auto SIGNAL_KEY_DOWN = "key down";
    constexpr auto SIGNAL_KEY_UP = "key up";
    constexpr auto SIGNAL_KEY_REPEAT = "key repeat";

    using KeyDownSlot = std::function<void(int key, int mods)>;

    constexpr auto SIGNAL_MOUSE_MOVE = "mouse move";
    constexpr auto SIGNAL_MOUSE_ENTER = "mouse enter";
    constexpr auto SIGNAL_MOUSE_LEAVE = "mouse leave";
    constexpr auto SIGNAL_MOUSE_WHEEL = "mouse wheel";
    constexpr auto SIGNAL_MOUSE_LEFT_DOWN = "mouse left down";
    constexpr auto SIGNAL_MOUSE_LEFT_UP = "mouse left up";
    constexpr auto SIGNAL_MOUSE_RIGHT_DOWN = "mouse right down";
    constexpr auto SIGNAL_MOUSE_RIGHT_UP = "mouse right up";
    constexpr auto SIGNAL_MOUSE_MIDDLE_DOWN = "mouse middle down";
    constexpr auto SIGNAL_MOUSE_MIDDLE_UP = "mouse middle up";
    constexpr auto SIGNAL_MOUSE_DOUBLE_CLICK = "mouse double click";

    using MouseMoveSlot = std::function<void(float x, float y)>;
    using MouseEnterSlot = std::function<void()>;
    using MouseLeaveSlot = std::function<void()>;
    using MouseWheelSlot = std::function<void(float x, float y)>;
    using MouseLeftDownSlot = std::function<void(float x, float y, int mods)>;
    using MouseLeftUpSlot = std::function<void(float x, float y, int mods)>;
    using MouseRightDownSlot = std::function<void(float x, float y, int mods)>;
    using MouseRightUpSlot = std::function<void(float x, float y, int mods)>;
    using MouseMiddleDownSlot = std::function<void(float x, float y, int mods)>;
    using MouseMiddleUpSlot = std::function<void(float x, float y, int mods)>;
    using MouseDoubleClickSlot = std::function<void(float x, float y, int mods)>;

    constexpr auto SIGNAL_WINDOW_RESIZE = "window resize";
    using WindowResizeSlot = std::function<void(int width, int height)>;

}  // namespace WorldEngine

#endif  // WORLDENGINE_ISIGNALDEFINE_H
