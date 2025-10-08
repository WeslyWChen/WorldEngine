//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_APPAPI_H
#define WORLDENGINE_APPAPI_H

#ifdef _WIN32
#ifdef WE_APP_BUILD
#define WE_APP_API __declspec(dllexport)
#else
#define WE_APP_API __declspec(dllimport)
#endif
#else
#define WE_APP_API
#endif

#endif  // WORLDENGINE_APPAPI_H
