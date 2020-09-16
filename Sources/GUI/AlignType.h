#pragma once

#include <string>

namespace GUI
{
    enum class AlignType
    {
        None,
        Top,
        Bottom,
        Left,
        Right,
        Fill,
        Center
    };

    AlignType strToAlign(const std::string& val);
}
