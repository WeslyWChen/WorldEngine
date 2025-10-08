//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_RENDEROPENGLAPI_H
#define WORLDENGINE_RENDEROPENGLAPI_H

#ifdef _WIN32
#ifdef WE_RENDEROPENGL_BUILD
#define WE_RENDEROPENGL_API __declspec(dllexport)
#else
#define WE_RENDEROPENGL_API __declspec(dllimport)
#endif
#else
#define WE_RENDEROPENGL_API
#endif

#endif  // WORLDENGINE_RENDEROPENGLAPI_H
