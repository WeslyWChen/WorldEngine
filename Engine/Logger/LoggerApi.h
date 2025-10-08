//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_LOGGERAPI_H
#define WORLDENGINE_LOGGERAPI_H

#ifdef _WIN32
#ifdef WELOGGER_BUILD
#define WELOGGER_API __declspec(dllexport)
#else
#define WELOGGER_API __declspec(dllimport)
#endif
#else
#define WELOGGER_API
#endif

#endif  // WORLDENGINE_LOGGERAPI_H
