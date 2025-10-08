//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_MODULEAPI_H
#define WORLDENGINE_MODULEAPI_H

#ifdef _WIN32
#ifdef WE_MODULE_BUILD
#define WE_MODULE_API __declspec(dllexport)
#else
#define WE_MODULE_API __declspec(dllimport)
#endif
#else
#define WE_MODULE_API
#endif

#endif  // WORLDENGINE_MODULEAPI_H
