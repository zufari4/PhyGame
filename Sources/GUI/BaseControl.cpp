#include "BaseControl.h"

namespace GUI
{
    BaseControl::BaseControl(const std::string& name, ControlType type, BaseControl* parent /*= nullptr*/)
        : name_(name)
        , type_(type)
        , parent_(parent)
        , pos_(0, 0)
        , size_(0, 0)
        , visible_(true)
        , align_(AlignType::None)
        , margin_{0,0,0,0}
        , padding_{0,0,0,0}
        , rounding_(0)
    {
        if (parent) {
            std::unique_ptr<BaseControl> ctrl = std::unique_ptr<BaseControl>(this);
            parent->AddControl(std::move(ctrl));
        }
    }

    BaseControl::~BaseControl() {}

    ControlType BaseControl::GetType() const
    { 
        return type_; 
    }
    const std::string& BaseControl::GetName() const 
    { 
        return name_; 
    }

    void BaseControl::AddControl(std::unique_ptr<BaseControl> ctrl)
    {
        controls_.push_back(std::move(ctrl));
    }

    void BaseControl::SetPos(int x, int y, int width, int height)
    {
        pos_.x = (float)x; pos_.y = (float)y; size_.y = (float)height; size_.x = (float)width;
    }

    void BaseControl::Render()
    {
    }

    void BaseControl::SetVisible(bool val)
    {
        visible_ = val;
    }

    bool BaseControl::IsVisible() const
    {
        return visible_;
    }

    void BaseControl::SetAlign(AlignType val)
    {
        align_ = val;
    }

    GUI::AlignType BaseControl::GetAlign() const
    {
        return align_;
    }

    int BaseControl::GetWidth() const
    {
        return (int)size_.x;
    }

    int BaseControl::GetHeight() const
    {
        return (int)size_.y;
    }

    int BaseControl::GetPosX() const
    {
        return (int)pos_.x;
    }

    int BaseControl::GetPosY() const
    {
        return (int)pos_.y;
    }

    std::vector<std::unique_ptr<BaseControl>>* BaseControl::GetControls()
    {
        return &controls_;
    }

    void BaseControl::SetMargin(int left, int top, int right, int bottom)
    {
        margin_[0] = left;
        margin_[1] = top;
        margin_[2] = right;
        margin_[3] = bottom;
    }

    const std::array<int,4>& BaseControl::GetMargin() const
    {
        return margin_;
    }

    void BaseControl::SetPadding(int left, int top, int right, int bottom)
    {
        padding_[0] = left;
        padding_[1] = top;
        padding_[2] = right;
        padding_[3] = bottom;
    }

    const std::array<int, 4>& BaseControl::GetPadding() const
    {
        return padding_;
    }

    void BaseControl::SetRounding(float val)
    {
        rounding_ = val;
    }

    float BaseControl::GetRounding() const
    {
        return rounding_;
    }

    void BaseControl::SetFont(ImFont* font)
    {
        font_ = font;
    }

    void BaseControl::SetFileActivate(const std::string& fileName)
    {
        fileActivate_ = fileName;
    }

    const std::string& BaseControl::GetFileActivate() const
    {
        return fileActivate_;
    }

    bool BaseControl::CursorAtWidget(int x, int y) const
    {
        return x >= pos_.x && x <= pos_.x + size_.x && y >= pos_.y && y <= pos_.y + size_.y;
    }

}