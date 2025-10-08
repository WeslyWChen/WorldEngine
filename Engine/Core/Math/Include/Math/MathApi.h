//
// Created by 30632 on 2025/10/2.
//

#ifndef WORLDENGINE_MATHAPI_H
#define WORLDENGINE_MATHAPI_H

#ifdef _WIN32
#ifdef WE_MATH_BUILD
#define WE_MATH_API __declspec(dllexport)
#else
#define WE_MATH_API __declspec(dllimport)
#endif
#else
#define WE_MATH_API
#endif

#endif  // WORLDENGINE_MATHAPI_H
