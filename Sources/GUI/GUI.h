#pragma once

#include <string>

#define LIB_API __declspec(dllexport)
struct SDL_Window;

namespace GUI
{
    LIB_API void Init(SDL_Window* window, void* glContext, const std::string& configFile);
    LIB_API void Free();
    LIB_API void ProcessFrame();
}