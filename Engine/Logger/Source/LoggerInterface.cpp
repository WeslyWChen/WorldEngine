//
// Created by 30632 on 2025/10/8.
//

#include "Logger/LoggerInterface.h"

#include <cstdarg>

#include "spdlog/spdlog.h"

using namespace std;
using namespace WorldEngine;

static spdlog::level::level_enum convert(Level level)
{
    switch (level) {
        case Level::Trace:
            return spdlog::level::trace;
        case Level::Debug:
            return spdlog::level::debug;
        case Level::Info:
            return spdlog::level::info;
        case Level::Warning:
            return spdlog::level::warn;
        case Level::Error:
            return spdlog::level::err;
        case Level::Fatal:
            return spdlog::level::critical;
        default:
            return spdlog::level::info;
    }
}

void WorldEngine::LogImpl(Level level, const std::string& message)
{
    spdlog::log(convert(level), message);
}