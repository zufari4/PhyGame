#pragma once

#include <string>

namespace GUI 
{
    enum class TextAlign
    {
        Undefined,
        TopLeft,
        TopCenter,
        TopRight,
        MiddleLeft,
        MiddleCenter,
        MiddleRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };

    TextAlign strToTextAlign(const std::string& s);
}



