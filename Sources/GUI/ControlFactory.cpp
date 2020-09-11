#include "ControlFactory.h"

namespace GUI
{
    Button::Button(const std::string& name, BaseControl* parent)
        : BaseControl(name, ControlType::Button, parent)
    {

    }
    
    void Button::SetText(const std::string& text)
    {
        text_ = text;
    }

    std::unique_ptr<Button> createControlButton(const std::string& name, BaseControl* parent /*= nullptr*/)
    {
        auto ctrl = std::make_unique<Button>(name, parent);
        return ctrl;
    }

}