//
// Created by 30632 on 2025/10/8.
//

#include "LoggerInterface.h"

#include <cstdarg>

#include "spdlog/spdlog.h"

using namespace std;
using namespace WorldEngine;

static spdlog::level::level_enum convert(Level level)
{
    switch (level) {
        case Level::TRACE:
            return spdlog::level::trace;
        case Level::DEBUG:
            return spdlog::level::debug;
        case Level::INFO:
            return spdlog::level::info;
        case Level::WARNING:
            return spdlog::level::warn;
        case Level::ERROR:
            return spdlog::level::err;
        case Level::FATAL:
            return spdlog::level::critical;
        default:
            return spdlog::level::info;
    }
}

void WorldEngine::LogImpl(Level level, const std::string& message)
{
    spdlog::log(convert(level), message);
}