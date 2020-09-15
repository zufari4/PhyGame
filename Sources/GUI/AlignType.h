#pragma once

#include <string>

namespace GUI
{
    enum class AlignType
    {
        None,
        Top,
        Botton,
        Left,
        Right,
        Fill
    };

    AlignType strToAlign(const std::string& val);
}
