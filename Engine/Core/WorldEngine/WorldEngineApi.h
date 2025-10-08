//
// Created by 30632 on 2025/10/2.
//

#ifndef WORLDENGINE_WORLDENGINEAPI_H
#define WORLDENGINE_WORLDENGINEAPI_H

#ifdef _WIN32
#ifdef WORLDENGINE_BUILD
#define WORLDENGINE_API __declspec(dllexport)
#else
#define WORLDENGINE_API __declspec(dllimport)
#endif
#else
#define WORLDENGINE_API
#endif

#endif  // WORLDENGINE_WORLDENGINEAPI_H
