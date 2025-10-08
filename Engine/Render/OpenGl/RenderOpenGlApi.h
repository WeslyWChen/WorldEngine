//
// Created by 30632 on 2025/10/8.
//

#ifndef WORLDENGINE_RENDEROPENGLAPI_H
#define WORLDENGINE_RENDEROPENGLAPI_H

#ifdef _WIN32
#ifdef WERENDEROPENGL_BUILD
#define WERENDEROPENGL_API __declspec(dllexport)
#else
#define WERENDEROPENGL_API __declspec(dllimport)
#endif
#else
#define WERENDEROPENGL_API
#endif

#endif  // WORLDENGINE_RENDEROPENGLAPI_H
