#pragma once

#include "BaseControl.h"

namespace GUI
{
    class Header : public BaseControl
    {
    public:
        Header(const std::string& name, BaseControl* parent = nullptr);
        void SetText(const std::string& text);
        void Render() const override;
    private:
        std::string text_;
    };
}