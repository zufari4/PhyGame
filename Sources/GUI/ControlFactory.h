#pragma once

#include "BaseControl.h"
#include <memory>

namespace GUI
{
    std::unique_ptr<BaseControl> createControl(ControlType type, const std::string& name, BaseControl* parent = nullptr);
    tdControls LoadGUIFromFile(const std::string& descriptionFile);
}