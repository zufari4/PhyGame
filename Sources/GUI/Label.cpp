#include "Label.h"
#include "ControlTypes.h"

namespace GUI
{

    Label::Label(const std::string& name, BaseControl* parent /*= nullptr*/)
        : BaseControl(name, ControlType::Label, parent)
        , textColor_{1.0f, 1.0f, 1.0f, 1.0f}
        , bgColor_{ 1.0f, 1.0f, 1.0f, 0.0f }
        , textAlign_(TextAlign::Undefined)
    {

    }

    void Label::SetText(const std::string& text)
    {
        text_ = text;
    }

    void Label::SetBackgroundColor(const ImVec4& val)
    {
        bgColor_ = val;
    }

    void Label::SetTextColor(const ImVec4& val)
    {
        textColor_ = val;
    }

    void Label::SetTextAlign(const TextAlign val)
    {
        textAlign_ = val;
    }

    void Label::Render()
    {
        ImGui::SetCursorPos(pos_);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, bgColor_);

        ImGuiStyle& style = ImGui::GetStyle();
        const auto prevRounding = style.ChildRounding;
        const auto preBorder = style.WindowBorderSize;
        style.ChildRounding = rounding_;
        style.ChildBorderSize = 0;

        ImGui::BeginChild(("backgroundPanel" + name_).c_str(), size_, true,
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
        //
        const auto prevFrameRounding = style.FrameRounding;
        style.FrameRounding = rounding_;
        ImGui::PushFont(font_);
        calcTextPos();
        ImGui::SetCursorPos(textPos_);

        ImGui::TextColored(textColor_, text_.c_str());

        style.FrameRounding = prevFrameRounding;
        ImGui::PopFont();
        //
        ImGui::EndChild();
        ImGui::PopStyleColor(1);
    }

    void Label::calcTextPos()
    {
        const ImVec2 ts = ImGui::CalcTextSize(text_.c_str());
        switch (textAlign_)
        {
        case GUI::TextAlign::Undefined: textPos_.x = 0.0f; textPos_.y = 0.0f; break;
        case GUI::TextAlign::TopLeft: textPos_.x = 0.0f; textPos_.y = 0.0f; break;
        case GUI::TextAlign::TopCenter: textPos_.x = size_.x * 0.5f - ts.x * 0.5f; textPos_.y = 0; break;
        case GUI::TextAlign::TopRight: textPos_.x = size_.x * 0.5f + ts.x * 0.5f; textPos_.y = 0; break;
        case GUI::TextAlign::MiddleLeft: textPos_.x = 0.0f; textPos_.y = size_.y * 0.5f - ts.y * 0.5f; break;
        case GUI::TextAlign::MiddleCenter: textPos_.x = size_.x * 0.5f - ts.x * 0.5f; textPos_.y = size_.y * 0.5f - ts.y * 0.5f; break;
        case GUI::TextAlign::MiddleRight: textPos_.x = size_.x * 0.5f + ts.x * 0.5f; textPos_.y = size_.y * 0.5f - ts.y * 0.5f; break;
        case GUI::TextAlign::BottomLeft: textPos_.x = 0.0f; textPos_.y = size_.y * 0.5f + ts.y * 0.5f; break;
        case GUI::TextAlign::BottomCenter: textPos_.x = size_.x * 0.5f - ts.x * 0.5f; textPos_.y = size_.y * 0.5f + ts.y * 0.5f; break;
        case GUI::TextAlign::BottomRight: textPos_.x = size_.x * 0.5f + ts.x * 0.5f; textPos_.y = size_.y * 0.5f + ts.y * 0.5f; break;
        }
    }

}