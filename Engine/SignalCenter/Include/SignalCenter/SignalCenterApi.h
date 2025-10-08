//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_SIGNALCENTERAPI_H
#define WORLDENGINE_SIGNALCENTERAPI_H

#ifdef _WIN32
#ifdef WE_SIGNALCENTER_BUILD
#define WE_SIGNALCENTER_API __declspec(dllexport)
#else
#define WE_SIGNALCENTER_API __declspec(dllimport)
#endif
#else
#define WE_SIGNALCENTER_API
#endif

#endif  // WORLDENGINE_SIGNALCENTERAPI_H
