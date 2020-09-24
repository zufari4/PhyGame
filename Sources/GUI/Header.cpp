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
        text_ = text;
    }

    void Header::Render() const
    {
        ImGui::SetCursorPos(pos_);
        ImGuiStyle& style = ImGui::GetStyle();
        const auto prevRounding = style.FrameRounding;
        style.FrameRounding = rounding_;
        ImGui::PushFont(font_);
        ImGui::PushItemWidth(size_.y);

        ImGui::Text(text_.c_str());

        style.FrameRounding = prevRounding;
        ImGui::PopItemWidth();
        ImGui::PopFont();
    }

}