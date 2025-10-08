//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_SIGNALCENTERAPI_H
#define WORLDENGINE_SIGNALCENTERAPI_H

#ifdef _WIN32
#ifdef WESIGNALCENTER_BUILD
#define WESIGNALCENTER_API __declspec(dllexport)
#else
#define WESIGNALCENTER_API __declspec(dllimport)
#endif
#else
#define WESIGNALCENTER_API
#endif

#endif  // WORLDENGINE_SIGNALCENTERAPI_H
