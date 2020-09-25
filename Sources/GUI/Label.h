#pragma once

#include "BaseControl.h"
#include "TextAlign.h"

namespace GUI
{
    class Label : public BaseControl
    {
    public:
        Label(const std::string& name, BaseControl* parent = nullptr);
        void SetText(const std::string& text);
        void SetBackgroundColor(const ImVec4& val);
        void SetTextColor(const ImVec4& val);
        void SetTextAlign(const TextAlign val);
        void Render() override;
    private:
        void calcTextPos();

        std::string text_;
        ImVec4 textColor_;
        ImVec4 bgColor_;
        TextAlign textAlign_;
        ImVec2 textPos_;
    };
}