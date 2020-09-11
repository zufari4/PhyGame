#pragma once

#include <string>
#include <vector>

namespace GUI
{
    enum class ControlType;

    class BaseControl
    {
    public:
        BaseControl(const std::string& name, ControlType type, BaseControl* parent = nullptr) 
            : name_(name)
            , type_(type)
            , parent_(parent) 
            , x_(0)
            , y_(0)
            , width_(0)
            , height_(0)
            , visible_(true)
        {
            if (parent) parent->AddControl(this);
        }
        virtual ~BaseControl() {}
        ControlType GetType() const { return type_; }
        const std::string& GetName() const { return name_; }
        virtual void AddControl(BaseControl* child) { controls_.push_back(child); }
        virtual void SetPos(int x, int y, int width, int height) { x_ = x; y_ = y; width_ = width; height_ = height; }
    private:
        std::string name_;
        ControlType type_;
        BaseControl* parent_;
        std::vector<BaseControl*> controls_;
        int x_;
        int y_;
        int width_;
        int height_;
        bool visible_;
    };
}