//
// Created by 30632 on 2025/10/8.
//

#include <chrono>

#include "gtest/gtest.h"
#include "Module/ModuleInterface.h"
#include "SignalCenter/SignalCenterInterface.h"

using namespace std;
using namespace WorldEngine;

TEST(TestSignalCenter, Base)
{
    auto signalCenter = CreateSignalCenter();

    int count = 0;
    signalCenter->connect("test", [&count] { count++; });
    signalCenter->emitSignal("test");
    ASSERT_EQ(count, 1);

    signalCenter->emitSignal("test");
    ASSERT_EQ(count, 2);
}

TEST(TestSignalCenter, MainThreadRun)
{
    auto signalCenter = CreateSignalCenter();

    int count = 0;
    signalCenter->connect("test", [&count] { count++; });
    signalCenter->emitSignalMainThread("test");
    ASSERT_EQ(count, 0);
    signalCenter->runMainThread();
    ASSERT_EQ(count, 1);
}

TEST(TestSignalCenter, SignalThreadRun)
{
    using namespace std::chrono;

    auto signalCenter = CreateSignalCenter();
    signalCenter->startupSignalThread();

    int count = 0;
    signalCenter->connect("test", [&count] { count++; });
    signalCenter->emitSignalSignalThread("test");
    ASSERT_TRUE(count == 0 || count == 1);
    this_thread::sleep_for(500ms);
    signalCenter->shutdownSignalThread();
    EXPECT_EQ(count, 1);
}