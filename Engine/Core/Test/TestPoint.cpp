//
// Created by 30632 on 2025/10/2.
//

#include "gtest/gtest.h"
#include "Point4.h"

using namespace std;
using namespace WorldEngine;

TEST(TestPoint, Point)
{
    auto pt = Point::Make(1.f, 2.f);
    EXPECT_TRUE(pt.isFinite());
    EXPECT_TRUE(pt.length() == 2.23606797749979f);

    pt.normalize();
    EXPECT_TRUE(std::fabs(pt.length() - 1.f) < std::numeric_limits<float>::epsilon());

    pt.set(1.f, 2.f);
    EXPECT_EQ(Point::Make(1.f, 2.f), pt);

    auto dotV = Point::DotProduct(pt, pt);
    EXPECT_TRUE(std::fabs(dotV - 5.f) < std::numeric_limits<float>::epsilon());

    dotV = Point::CrossProduct(pt, pt);
    EXPECT_TRUE(std::fabs(dotV) < std::numeric_limits<float>::epsilon());
}

TEST(TestPoint, Point3)
{
    Point3 pt = Point3::Make(1.f, 2.f, 3.f);
    EXPECT_EQ(Point3::Make(1.f, 2.f, 3.f), pt);
    EXPECT_TRUE(pt.normalize());
    EXPECT_TRUE(std::fabs(pt.length() - 1.f) < std::numeric_limits<float>::epsilon());

    pt.set(1.f, 2.f, 3.f);
    EXPECT_EQ(Point3::Make(1.f, 2.f, 3.f), pt);

    pt.offset(1.f, 2.f, 3.f);
    EXPECT_EQ(Point3::Make(2.f, 4.f, 6.f), pt);

    pt = Point3::Normalize(pt);
    EXPECT_TRUE(std::fabs(pt.length() - 1.f) < std::numeric_limits<float>::epsilon());

    auto pt2 = Point3::CrossProduct(pt, Point3::Make(1.f, 2.f, 3.f));
    EXPECT_EQ(Point3::Make(0.f, 0.f, 0.f), pt2);

    auto dotV = Point3::Distance(pt, Point3::Make(0.f, 0.f, 0.f));
    EXPECT_TRUE(std::fabs(dotV - 1.f) < std::numeric_limits<float>::epsilon());

    auto dotP = Point3::DotProduct(pt, Point3::Make(1.f, 2.f, 3.f));
    EXPECT_TRUE(std::fabs(dotP - 3.74165726f) < std::numeric_limits<float>::epsilon());
}

TEST(TestPoint, Point4)
{
    Point4 pt(1.f, 2.f, 3.f, 4.f);
    EXPECT_EQ(Point4::Make(1.f, 2.f, 3.f, 4.f), pt);
    EXPECT_EQ(pt.x, 1.f);
    EXPECT_EQ(pt.y, 2.f);
    EXPECT_EQ(pt.z, 3.f);
    EXPECT_EQ(pt.w, 4.f);

    auto len = pt.length();
    EXPECT_TRUE(std::fabs(len - 5.47722578f) < std::numeric_limits<float>::epsilon());

    pt.normalize();
    EXPECT_TRUE(std::fabs(pt.length() - 1.f) < std::numeric_limits<float>::epsilon());

    auto dotV = Point4::DotProduct(pt, Point4::Make(1.f, 2.f, 3.f, 4.f));
    EXPECT_TRUE(std::fabs(dotV - 5.4772253f) < std::numeric_limits<float>::epsilon());
}