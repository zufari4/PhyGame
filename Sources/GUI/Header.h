#pragma once

#include "BaseControl.h"

namespace GUI
{
    class Header : public BaseControl
    {
    public:
        Header(const std::string& name, BaseControl* parent = nullptr);
        void SetText(const std::string& text);
        void Render() override;
    private:
        char text_[1024];
    };
}