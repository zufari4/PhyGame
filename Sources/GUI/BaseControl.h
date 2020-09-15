#pragma once

#include <string>
#include <vector>
#include <memory>
#include "AlignType.h"
#include "imgui.h"

namespace GUI
{
    enum class ControlType;

    class BaseControl
    {
    public:
        BaseControl(const std::string& name, ControlType type, BaseControl* parent = nullptr);
        virtual ~BaseControl();
        virtual ControlType GetType() const;
        virtual const std::string& GetName() const;
        virtual void AddControl(std::unique_ptr<BaseControl> ctrl);
        virtual void SetPos(int x, int y, int width, int height);
        virtual void Render() const;
        virtual void SetVisible(bool val);
        virtual bool IsVisible() const;
        virtual void SetAlign(AlignType val);
        virtual AlignType GetAlign() const;
    protected:
        std::string name_;
        ControlType type_;
        BaseControl* parent_;
        std::vector<std::unique_ptr<BaseControl>> controls_;
        ImVec2 pos_;
        ImVec2 size_;
        bool visible_;
        AlignType align_;
    };

    using tdControls = std::vector<std::unique_ptr<BaseControl>>;
}