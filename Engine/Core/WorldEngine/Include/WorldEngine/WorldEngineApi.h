//
// Created by 30632 on 2025/10/2.
//

#ifndef WORLDENGINE_WORLDENGINEAPI_H
#define WORLDENGINE_WORLDENGINEAPI_H

#ifdef _WIN32
#ifdef WE_WORLDENGINE_BUILD
#define WE_WORLDENGINE_API __declspec(dllexport)
#else
#define WE_WORLDENGINE_API __declspec(dllimport)
#endif
#else
#define WE_WORLDENGINE_API
#endif

#endif  // WORLDENGINE_WORLDENGINEAPI_H
