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
        ImGui::SetNextWindowSize(size_);
        ImGui::PushStyleColor(ImGuiCol_WindowBg, bgColor_);

        ImGuiStyle& style = ImGui::GetStyle();
        const auto prevPadding = style.WindowPadding;
        const auto prevRounding = style.WindowRounding;
        style.WindowPadding = zeroVec2;
        style.WindowRounding = 0;
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
        style.WindowPadding = prevPadding;
        style.WindowRounding = prevRounding;
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