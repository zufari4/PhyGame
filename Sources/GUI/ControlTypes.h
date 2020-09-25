#pragma once

#include <string>

namespace GUI
{
    enum class ControlType
    {
        Unknown,
        Window,
        Panel,
        Button,
        Label,
        TextBox,
        CheckBox,
    };

    ControlType strToControlType(const std::string& str);
}