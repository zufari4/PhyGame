#include "Button.h"
#include "ControlTypes.h"
#include "EventManager.h"
#include "EventType.h"

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
        ImGuiStyle& style = ImGui::GetStyle();
        const auto prevRounding = style.FrameRounding;
        style.FrameRounding = rounding_;
        ImGui::PushFont(font_);
        if (ImGui::Button(text_.c_str(), size_)) ClickHandler();

        style.FrameRounding = prevRounding;
        ImGui::PopFont();
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

    void Button::ClickHandler() const
    {
        EventManager::PushEvent(EventManager::EventType::ButtonClick, name_);
    }

}