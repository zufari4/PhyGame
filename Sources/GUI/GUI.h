#pragma once

#include <string>

#define LIB_API __declspec(dllexport)
struct SDL_Window;

namespace GUI
{
    LIB_API void Init(SDL_Window* window, void* glContext, const std::string& configFile, const std::string& resourceDirectory);
    LIB_API void Free();
    LIB_API void ProcessFrame();
    LIB_API void LoadGUI(const std::string& jsonFile);
    LIB_API bool CursorAtWidget(int x, int y);
}