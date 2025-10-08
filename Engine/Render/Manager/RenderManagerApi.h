//
// Created by 30632 on 2025/10/7.
//

#ifndef WORLDENGINE_RENDERMANAGERAPI_H
#define WORLDENGINE_RENDERMANAGERAPI_H

#ifdef _WIN32
#ifdef WERENDERMANAGER_BUILD
#define WERENDERMANAGER_API __declspec(dllexport)
#else
#define WERENDERMANAGER_API __declspec(dllimport)
#endif
#else
#define WERENDERMANAGER_API
#endif

#endif  // WORLDENGINE_RENDERMANAGERAPI_H
