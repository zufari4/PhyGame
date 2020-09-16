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

    void BaseControl::Render() const
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

}