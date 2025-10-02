//
// Created by 30632 on 2025/10/2.
//

#include <complex>

#include "Color.h"
#include "gtest/gtest.h"

using namespace std;
using namespace WorldEngine;

TEST(TestColor, Base)
{
    ASSERT_EQ(ColorGetA(ColorMakeARGB(10, 20, 30, 40)), 10);
    ASSERT_EQ(ColorGetR(ColorMakeARGB(10, 20, 30, 40)), 20);
    ASSERT_EQ(ColorGetG(ColorMakeARGB(10, 20, 30, 40)), 30);
    ASSERT_EQ(ColorGetB(ColorMakeARGB(10, 20, 30, 40)), 40);

    ASSERT_EQ(ColorGetA(ColorMakeRGBA(10, 20, 30, 40)), 40);
    ASSERT_EQ(ColorGetR(ColorMakeRGBA(10, 20, 30, 40)), 10);
    ASSERT_EQ(ColorGetG(ColorMakeRGBA(10, 20, 30, 40)), 20);
    ASSERT_EQ(ColorGetB(ColorMakeRGBA(10, 20, 30, 40)), 30);

    ASSERT_EQ(ColorGetA(ColorMakeRGB(10, 20, 30)), 255);
    ASSERT_EQ(ColorGetR(ColorMakeRGB(10, 20, 30)), 10);
    ASSERT_EQ(ColorGetG(ColorMakeRGB(10, 20, 30)), 20);
    ASSERT_EQ(ColorGetB(ColorMakeRGB(10, 20, 30)), 30);

    ASSERT_EQ(ColorMakeARGB(10, 20, 30, 40), ColorSetA(ColorMakeARGB(10, 20, 30, 40), 10));
    ASSERT_EQ(ColorMakeARGB(10, 20, 30, 40), ColorSetR(ColorMakeARGB(10, 20, 30, 40), 20));
    ASSERT_EQ(ColorMakeARGB(10, 20, 30, 40), ColorSetG(ColorMakeARGB(10, 20, 30, 40), 30));
    ASSERT_EQ(ColorMakeARGB(10, 20, 30, 40), ColorSetB(ColorMakeARGB(10, 20, 30, 40), 40));
    ASSERT_EQ(ColorMakeRGBA(10, 20, 30, 40), ColorSetA(ColorMakeRGBA(10, 20, 30, 40), 40));
    ASSERT_EQ(ColorMakeRGBA(10, 20, 30, 40), ColorSetR(ColorMakeRGBA(10, 20, 30, 40), 10));
    ASSERT_EQ(ColorMakeRGBA(10, 20, 30, 40), ColorSetG(ColorMakeRGBA(10, 20, 30, 40), 20));
    ASSERT_EQ(ColorMakeRGBA(10, 20, 30, 40), ColorSetB(ColorMakeRGBA(10, 20, 30, 40), 30));
    ASSERT_EQ(ColorMakeRGB(10, 20, 30), ColorSetA(ColorMakeRGB(10, 20, 30), 255));
    ASSERT_EQ(ColorMakeRGB(10, 20, 30), ColorSetR(ColorMakeRGB(10, 20, 30), 10));
    ASSERT_EQ(ColorMakeRGB(10, 20, 30), ColorSetG(ColorMakeRGB(10, 20, 30), 20));
    ASSERT_EQ(ColorMakeRGB(10, 20, 30), ColorSetB(ColorMakeRGB(10, 20, 30), 30));
}

TEST(TestColor, Convert)
{
    using namespace WorldEngine::ColorUtil;

    auto color = ColorMakeARGB(10, 20, 30, 40);
    auto colorF = convertToColorF(color);
    EXPECT_GT(0.0001f, std::fabs(colorF.a - 10.f / 255.f));
    EXPECT_GT(0.0001f, std::fabs(colorF.r - 20.f / 255.f));
    EXPECT_GT(0.0001f, std::fabs(colorF.g - 30.f / 255.f));
    EXPECT_GT(0.0001f, std::fabs(colorF.b - 40.f / 255.f));
}

TEST(TestColor, Simple)
{
    using namespace WorldEngine::ColorUtil;

    ASSERT_EQ(0x00, ColorMakeARGB(0, 0, 0, 0));

    ASSERT_EQ(0xFF000000, ColorMakeARGB(0xFF, 0, 0, 0));

    ASSERT_EQ(0xFF0000FF, ColorMakeARGB(0xFF, 0, 0, 0xFF));

    ASSERT_EQ(0xFFFF0000, ColorMakeARGB(0xFF, 0xFF, 0, 0));

    HSV hsv = convertToHsv(ColorTransparent);
    EXPECT_EQ(hsv.h, 0);
    EXPECT_EQ(hsv.s, 0);
    EXPECT_EQ(hsv.v, 0);

    hsv = convertToHsv(ColorWhite);
    EXPECT_EQ(hsv.h, 0);
    EXPECT_EQ(hsv.s, 0);
    EXPECT_EQ(hsv.v, 1);

    hsv = convertToHsv(ColorBlack);
    EXPECT_EQ(hsv.h, 0);
    EXPECT_EQ(hsv.s, 0);
    EXPECT_EQ(hsv.v, 0);

    hsv = convertToHsv(ColorRed);
    EXPECT_EQ(hsv.h, 0);
    EXPECT_EQ(hsv.s, 1);
    EXPECT_EQ(hsv.v, 1);

    hsv = convertToHsv(ColorGreen);
    EXPECT_EQ(hsv.h, 120);
    EXPECT_EQ(hsv.s, 1);
    EXPECT_EQ(hsv.v, 1);

    hsv = convertToHsv(ColorBlue);
    EXPECT_EQ(hsv.h, 240);
    EXPECT_EQ(hsv.s, 1);
    EXPECT_EQ(hsv.v, 1);

    ColorF colorF = convertToColorF(ColorTransparent);
    EXPECT_EQ(colorF.r, 0);
    EXPECT_EQ(colorF.g, 0);
    EXPECT_EQ(colorF.b, 0);
    EXPECT_EQ(colorF.a, 0);

    colorF = convertToColorF(ColorBlack);
    EXPECT_EQ(colorF.r, 0);
    EXPECT_EQ(colorF.g, 0);
    EXPECT_EQ(colorF.b, 0);
    EXPECT_EQ(colorF.a, 1);

    colorF = convertToColorF(ColorWhite);
    EXPECT_EQ(colorF.r, 1);
    EXPECT_EQ(colorF.g, 1);
    EXPECT_EQ(colorF.b, 1);
    EXPECT_EQ(colorF.a, 1);

    colorF = convertToColorF(ColorRed);
    EXPECT_EQ(colorF.r, 1);
    EXPECT_EQ(colorF.g, 0);
    EXPECT_EQ(colorF.b, 0);
    EXPECT_EQ(colorF.a, 1);

    colorF = convertToColorF(ColorGreen);
    EXPECT_EQ(colorF.r, 0);
    EXPECT_EQ(colorF.g, 1);
    EXPECT_EQ(colorF.b, 0);
    EXPECT_EQ(colorF.a, 1);

    colorF = convertToColorF(ColorBlue);
    EXPECT_EQ(colorF.r, 0);
    EXPECT_EQ(colorF.g, 0);
    EXPECT_EQ(colorF.b, 1);
    EXPECT_EQ(colorF.a, 1);
}