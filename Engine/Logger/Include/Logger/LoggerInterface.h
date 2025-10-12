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
        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
        Default = Info,
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
        WorldEngine::Log(Level::Trace, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_DEBUG(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::Debug, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_INFO(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::Info, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_WARNING(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::Warning, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_ERROR(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::Error, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void LOG_FATAL(std::format_string<Args...> format, Args&&... args)
    {
        WorldEngine::Log(Level::Fatal, format, std::forward<Args>(args)...);
    }

}  // namespace WorldEngine

#endif  // WORLDENGINE_LOGGERINTERFACE_H
