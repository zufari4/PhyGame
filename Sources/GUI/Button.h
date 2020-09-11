#pragma once

#include "BaseControl.h"

namespace GUI
{
    class Button : public BaseControl
    {
    public:
        Button(const std::string& name, BaseControl* parent = nullptr);
        void SetText(const std::string& text);
        void Render() const override;
    private:
        std::string text_;
    };
}