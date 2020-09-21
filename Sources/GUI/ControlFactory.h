#pragma once

#include "BaseControl.h"
#include <memory>

namespace json
{
    class Array;
}

namespace GUI
{
    std::unique_ptr<BaseControl> createControl(ControlType type, const std::string& name, BaseControl* parent = nullptr);
    tdControls CreateControls(const std::string& resourceDirectory, const json::Array& controls);
}