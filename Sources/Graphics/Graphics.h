#pragma once

#include <string>

#define LIB_API __declspec(dllexport)
struct SDL_Window;

namespace Graphics {
    LIB_API void Init(const std::string& configFile);
    LIB_API void ClearFrame();
    LIB_API void SwapFrame();
    LIB_API void SetVSync(bool enable);
    LIB_API void SetClearColor(float red, float green, float blue, float alpha);
    LIB_API SDL_Window* GetCurrentWindow();
    LIB_API void* GetOpenGLContext();
    LIB_API int GetFrameWidth();
    LIB_API int GetFrameHeight();
    LIB_API void SetCamera2D(float centerX, float centerY);
    LIB_API void DrawPoint(float x, float y);
}