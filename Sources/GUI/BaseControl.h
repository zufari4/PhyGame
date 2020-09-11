#pragma once

#include "imgui.h"
#include <string>
#include <vector>
#include <memory>

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
            , pos_(0, 0)
            , size_(0, 0)
            , visible_(true)
        {
            std::unique_ptr<BaseControl> ctrl = std::unique_ptr<BaseControl>(this);
            if (parent) parent->AddControl(std::move(ctrl));
        }
        virtual ~BaseControl() {}
        ControlType GetType() const { return type_; }
        const std::string& GetName() const { return name_; }
        virtual void AddControl(std::unique_ptr<BaseControl> ctrl)
        { 
            controls_.push_back(std::move(ctrl));
        }
        virtual void SetPos(int x, int y, int width, int height) { pos_.x = x; pos_.y = y; size_.x = height; size_.y = width; }
        virtual void Render() const {}
        virtual void SetVisible(bool val) { visible_ = val; }
    protected:
        std::string name_;
        ControlType type_;
        BaseControl* parent_;
        std::vector<std::unique_ptr<BaseControl>> controls_;
        ImVec2 pos_;
        ImVec2 size_;
        bool visible_;
    };

    using tdControls = std::vector<std::unique_ptr<BaseControl>>;
}