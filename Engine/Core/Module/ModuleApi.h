//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_MODULEAPI_H
#define WORLDENGINE_MODULEAPI_H

#ifdef _WIN32
#ifdef WEMODULE_BUILD
#define WEMODULE_API __declspec(dllexport)
#else
#define WEMODULE_API __declspec(dllimport)
#endif
#else
#define WEMODULE_API
#endif

#endif  // WORLDENGINE_MODULEAPI_H
