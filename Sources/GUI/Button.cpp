#include "Button.h"
#include "ControlTypes.h"

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

    void Button::Render() const
    {
        ImGui::SetCursorPos(pos_);
        ImGui::PushStyleColor(ImGuiCol_Text, textColor_);
        ImGui::PushStyleColor(ImGuiCol_Button, normalColor_);
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, hoverColor_);
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, activeColor_);
        ImGui::Button(text_.c_str(), size_);
        ImGui::PopStyleColor(4);
    }

    void Button::SetTextColor(const ImVec4& val)
    {
        textColor_ = val;
    }

    void Button::SetNormalColor(const ImVec4& val)
    {
        normalColor_ = val;
    }

    void Button::SetHoverColor(const ImVec4& val)
    {
        hoverColor_ = val;
    }

    void Button::SetActiveColor(const ImVec4& val)
    {
        activeColor_ = val;
    }

}