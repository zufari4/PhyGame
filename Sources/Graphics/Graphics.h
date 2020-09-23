#pragma once

#include <string>
#include <vector>
#include "Point.h"
#include "Color4f.h"

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
    LIB_API void DrawPoint(const Point& p, float pointSize, const Color4f& color);
    LIB_API void DrawPoints(const std::vector<Point>& v, float pointSize, const Color4f& color);
    LIB_API void DrawLines(const std::vector<Point>& v, const Color4f& color);
    LIB_API float win2worldX(float x);
    LIB_API float win2worldY(float y);
    LIB_API float world2winX(float x);
    LIB_API float world2winY(float y);
}