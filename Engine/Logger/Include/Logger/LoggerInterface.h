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

    WE_LOGGER_API void LogImpl(Level level, const std::string& message);

    template <typename... Args>
    void Log(Level level, std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::LogImpl(level, std::format(format, std::forward<Args>(args)...));
    }

    template <typename... Args>
    void LOG_TRACE(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::TRACE, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_DEBUG(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::DEBUG, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_INFO(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::INFO, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_WARNING(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::WARNING, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_ERROR(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::ERROR, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_FATAL(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::FATAL, format, std::forward<Args>(args)...);
    }

}  // namespace WorldEngine

#endif  // WORLDENGINE_LOGGERINTERFACE_H
