//
// Created by 30632 on 2025/10/2.
//

#ifndef WORLDENGINE_COLOR_H
#define WORLDENGINE_COLOR_H

#include <cassert>
#include <cstdint>

#include "MathApi.h"

namespace WorldEngine
{
    using Alpha = std::uint8_t;
    using Color = std::uint32_t;
    using PMColor = std::uint32_t;

    static constexpr inline Color ColorMakeARGB(std::uint8_t a, std::uint8_t r, std::uint8_t g, std::uint8_t b)
    {
        assert(a <= 255 && r <= 255 && g <= 255 && b <= 255);
        return (a << 24) | (r << 16) | (g << 8) | (b << 0);
    }

    static constexpr inline Color ColorMakeRGBA(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
    {
        return ColorMakeARGB(a, r, g, b);
    }

    static constexpr inline Color ColorMakeRGB(std::uint8_t r, std::uint8_t g, std::uint8_t b)
    {
        return ColorMakeARGB(255, r, g, b);
    }

    static constexpr inline std::uint8_t ColorGetA(Color color)
    {
        return (color >> 24) & 0xFF;
    }

    static constexpr inline std::uint8_t ColorGetR(Color color)
    {
        return (color >> 16) & 0xFF;
    }

    static constexpr inline std::uint8_t ColorGetG(Color color)
    {
        return (color >> 8) & 0xFF;
    }

    static constexpr inline std::uint8_t ColorGetB(Color color)
    {
        return color & 0xFF;
    }

    static constexpr inline Color ColorSetA(Color color, std::uint8_t a)
    {
        return (color & 0x00FFFFFF) | (a << 24);
    }

    static constexpr inline Color ColorSetR(Color color, std::uint8_t r)
    {
        return (color & 0xFF00FFFF) | (r << 16);
    }

    static constexpr inline Color ColorSetG(Color color, std::uint8_t g)
    {
        return (color & 0xFFFF00FF) | (g << 8);
    }

    static constexpr inline Color ColorSetB(Color color, std::uint8_t b)
    {
        return (color & 0xFFFFFF00) | (b << 0);
    }

    constexpr Color ColorTransparent = ColorMakeARGB(0, 0, 0, 0);

    constexpr Color ColorBlack = ColorMakeARGB(255, 0, 0, 0);
    constexpr Color ColorDkGray = ColorMakeARGB(255, 68, 68, 68);
    constexpr Color ColorGray = ColorMakeARGB(255, 136, 136, 136);
    constexpr Color ColorLtGray = ColorMakeARGB(255, 204, 204, 204);
    constexpr Color ColorWhite = ColorMakeARGB(255, 255, 255, 255);

    constexpr Color ColorRed = ColorMakeARGB(255, 255, 0, 0);
    constexpr Color ColorGreen = ColorMakeARGB(255, 0, 255, 0);
    constexpr Color ColorBlue = ColorMakeARGB(255, 0, 0, 255);
    constexpr Color ColorYellow = ColorMakeARGB(255, 255, 255, 0);
    constexpr Color ColorCyan = ColorMakeARGB(255, 0, 255, 255);
    constexpr Color ColorMagenta = ColorMakeARGB(255, 255, 0, 255);

    struct ColorF {
        float r = 0.f;
        float g = 0.f;
        float b = 0.f;
        float a = 0.f;
    };

    struct HSV {
        float h = 0.f;
        float s = 0.f;
        float v = 0.f;
    };

    namespace ColorUtil
    {
        WEMATH_API Color convertToColor(const ColorF& colorF);
        WEMATH_API Color convertToColor(const HSV& hsv);

        WEMATH_API ColorF convertToColorF(const Color& color);
        WEMATH_API ColorF convertToColorF(const HSV& hsv);

        WEMATH_API HSV convertToHsv(const Color& color);
        WEMATH_API HSV convertToHsv(const ColorF& colorF);
    }  // namespace ColorUtil

}  // namespace WorldEngine

#endif  // WORLDENGINE_COLOR_H
