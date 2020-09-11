#pragma once

#include "BaseControl.h"
#include <memory>

namespace GUI
{
    enum class ControlType
    {
        Window,
        Panel,
        Button,
        Label,
        TextBox,
        CheckBox,
    };

    class Button : public BaseControl
    {
    public:
        Button(const std::string& name, BaseControl* parent = nullptr);
        void SetText(const std::string& text);
    private:
        std::string text_;
    };

    std::unique_ptr<Button> createControlButton(const std::string& name, BaseControl* parent = nullptr);
}