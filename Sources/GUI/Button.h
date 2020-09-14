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
        void SetTextColor(const ImVec4& val);
        void SetNormalColor(const ImVec4& val);
        void SetHoverColor(const ImVec4& val);
        void SetActiveColor(const ImVec4& val);
    private:
        void ClickHandler() const;
        std::string text_;
        ImVec4 textColor_;
        ImVec4 normalColor_;
        ImVec4 hoverColor_;
        ImVec4 activeColor_;
    };
}