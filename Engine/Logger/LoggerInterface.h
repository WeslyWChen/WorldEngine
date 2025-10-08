//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_LOGGERINTERFACE_H
#define WORLDENGINE_LOGGERINTERFACE_H

#include <cstdint>
#include <format>
#include <string>

#include "LoggerApi.h"

namespace WorldEngine
{
    enum class Level : std::uint8_t {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL,
        DEFAULT = INFO,
    };

    WELOGGER_API void LogImpl(Level level, const std::string& message);

    template <typename... Args>
    void Log(Level level, std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::LogImpl(level, std::format(format, std::forward<Args>(args)...));
    }

}  // namespace WorldEngine

#endif  // WORLDENGINE_LOGGERINTERFACE_H
