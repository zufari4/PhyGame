#include "Header.h"
#include "ControlTypes.h"

namespace GUI
{

    Header::Header(const std::string& name, BaseControl* parent /*= nullptr*/)
        : BaseControl(name, ControlType::Header, parent)
    {

    }

    void Header::SetText(const std::string& text)
    {
        strcpy_s(text_, text.c_str());
    }

    void Header::Render()
    {
        ImGui::SetCursorPos(pos_);
        ImGuiStyle& style = ImGui::GetStyle();
        const auto prevRounding = style.FrameRounding;
        style.FrameRounding = rounding_;
        ImGui::PushFont(font_);
        ImGui::PushItemWidth(size_.x);

        ImGui::InputText("", text_, sizeof(text_), ImGuiInputTextFlags_ReadOnly | ImGuiInputTextFlags_NoHorizontalScroll | ImGuiInputTextFlags_NoUndoRedo);

        style.FrameRounding = prevRounding;
        ImGui::PopItemWidth();
        ImGui::PopFont();
    }

}