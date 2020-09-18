#include "Panel.h"
#include "ControlTypes.h"

namespace GUI
{

    Panel::Panel(const std::string& name, BaseControl* parent /*= nullptr*/)
        : BaseControl(name, ControlType::Panel, parent)
    {

    }

    void Panel::Render() const
    {
        ImGui::SetNextWindowPos(pos_, 0, zeroVec2);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, bgColor_);

        ImGuiStyle& style = ImGui::GetStyle();
        const auto prevRounding = style.ChildRounding;
        const auto preBorder = style.WindowBorderSize;
        style.ChildRounding = rounding_;
        style.ChildBorderSize = 0;

        ImGui::BeginChild(name_.c_str(), size_, true,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoBringToFrontOnFocus
        );
        style.ChildRounding = prevRounding;
        style.ChildBorderSize = preBorder;

        for (auto& ctrl : controls_) {
            if (ctrl->IsVisible()) ctrl->Render();
        }

        ImGui::EndChild();
        ImGui::PopStyleColor(1);
    }

    void Panel::SetBgColor(const ImVec4& color)
    {
        bgColor_ = color;
    }

}