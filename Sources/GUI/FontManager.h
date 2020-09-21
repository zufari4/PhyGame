#pragma once

#include "imgui.h"
#include <string>

namespace GUI
{
    namespace FontManager
    {
        ImFont* CreateFont(const std::string& fileName, float size, unsigned hintType);
    };
}