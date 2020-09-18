#pragma once

#include <string>
#include <vector>
#include <memory>
#include <array>
#include "AlignType.h"
#include "imgui.h"

static const ImVec2 zeroVec2{ 0, 0 };

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
        virtual int GetWidth() const;
        virtual int GetHeight() const;
        virtual int GetPosX() const;
        virtual int GetPosY() const;
        virtual std::vector<std::unique_ptr<BaseControl>>* GetControls();
        virtual void SetMargin(int left, int top, int right, int bottom);
        virtual const std::array<int, 4>& GetMargin() const;
        virtual void SetPadding(int left, int top, int right, int bottom);
        virtual const std::array<int, 4>& GetPadding() const;
        virtual void SetRounding(float val);
        virtual float GetRounding() const;
    protected:
        std::string name_;
        ControlType type_;
        BaseControl* parent_;
        std::vector<std::unique_ptr<BaseControl>> controls_;
        ImVec2 pos_;
        ImVec2 size_;
        bool visible_;
        AlignType align_;
        std::array<int, 4> margin_;
        std::array<int, 4> padding_;
        float rounding_;
    };

    using tdControls = std::vector<std::unique_ptr<BaseControl>>;
}