//
// Created by 30632 on 2025/10/10.
//

#ifndef WORLDENGINE_GAMEENGINEAPI_H
#define WORLDENGINE_GAMEENGINEAPI_H

#ifdef _WIN32
#ifdef WE_GAMEENGINE_BUILD
#define WE_GAMEENGINE_API __declspec(dllexport)
#else
#define WE_GAMEENGINE_API __declspec(dllimport)
#endif
#else
#define WE_GAMEENGINE_API
#endif

#endif  // WORLDENGINE_GAMEENGINEAPI_H
