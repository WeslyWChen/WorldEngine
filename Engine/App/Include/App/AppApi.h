//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_APPAPI_H
#define WORLDENGINE_APPAPI_H

#ifdef _WIN32
#ifdef WEAPP_BUILD
#define WEAPP_API __declspec(dllexport)
#else
#define WEAPP_API __declspec(dllimport)
#endif
#else
#define WEAPP_API
#endif

#endif  // WORLDENGINE_APPAPI_H
