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
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.5f, 0.9f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.6f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.4f, 0.8f, 1.0f));
        ImGui::Button(text_.c_str(), size_);
        ImGui::PopStyleColor(3);
    }

}