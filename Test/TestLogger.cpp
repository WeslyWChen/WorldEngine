//
// Created by 30632 on 2025/10/8.
//

#include "gtest/gtest.h"
#include "LoggerInterface.h"

using namespace std;
using namespace WorldEngine;

class TestLogger : public ::testing::Test {
protected:
    void SetUp() override { Log(Level::INFO, "TestLogger::SetUp"); }

    void TearDown() override { Log(Level::INFO, "TestLogger::TearDown"); }
};

TEST_F(TestLogger, Log)
{
    Log(Level::DEBUG, "TestLogger::Log");

    Log(Level::INFO, "TestLogger::Log");
}