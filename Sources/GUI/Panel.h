#pragma once

#include "BaseControl.h"

namespace GUI
{
    class Panel: public BaseControl
    {
    public:
        Panel(const std::string& name, BaseControl* parent = nullptr);
        void Render() const override;
        void SetBgColor(const ImVec4& color);
    private:
        ImVec4 bgColor_;
    };

}