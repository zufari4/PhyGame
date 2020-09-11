#pragma once

#include <string>

#define LIB_API __declspec(dllexport)
struct SDL_Window;

namespace GUI
{
    LIB_API void Init(SDL_Window* window, const std::string& configFile, const std::string& resourcesPath);
    LIB_API void ProcessFrame();
}