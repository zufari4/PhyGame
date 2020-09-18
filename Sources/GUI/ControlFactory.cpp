#include "ControlFactory.h"
#include "ControlTypes.h"
#include "Button.h"
#include "Panel.h"
#include "Utils.h"
#include "AlignType.h"
#include "elements.h"
#include "reader.h"

namespace GUI
{
    std::unique_ptr<BaseControl> createControl(ControlType type, const std::string& name, BaseControl* parent /*= nullptr*/)
    {
        std::unique_ptr<BaseControl> ctrl;

        switch (type)
        {
        case GUI::ControlType::Window:
            break;
        case GUI::ControlType::Panel:
            ctrl = std::make_unique<Panel>(name, parent);
            break;
        case GUI::ControlType::Button:
            ctrl = std::make_unique<Button>(name, parent);
            break;
        case GUI::ControlType::Label:
            break;
        case GUI::ControlType::TextBox:
            break;
        case GUI::ControlType::CheckBox:
            break;
        default:
            break;
        }

        return ctrl;
    }

    std::unique_ptr<BaseControl> CreateControl(const json::Object jsonObj)
    {
        std::unique_ptr<BaseControl> ctrl;

        auto paramIt = jsonObj.Find("type");
        if (paramIt == jsonObj.End()) {
            throw std::runtime_error("Parameter 'type' not found");
        }
        const ControlType type = strToControlType(static_cast<const json::String&>(paramIt->element).Value());

        paramIt = jsonObj.Find("name");
        if (paramIt == jsonObj.End()) {
            throw std::runtime_error("Parameter 'name' not found");
        }
        const std::string& name = static_cast<const json::String&>(paramIt->element).Value();

        paramIt = jsonObj.Find("posX");
        if (paramIt == jsonObj.End()) {
            throw std::runtime_error("Parameter 'posX' not found");
        }
        const int posX = static_cast<int>(static_cast<const json::Number&>(paramIt->element).Value());

        paramIt = jsonObj.Find("posY");
        if (paramIt == jsonObj.End()) {
            throw std::runtime_error("Parameter 'posY' not found");
        }
        const int posY = static_cast<int>(static_cast<const json::Number&>(paramIt->element).Value());

        paramIt = jsonObj.Find("width");
        if (paramIt == jsonObj.End()) {
            throw std::runtime_error("Parameter 'width' not found");
        }
        const int width = static_cast<int>(static_cast<const json::Number&>(paramIt->element).Value());

        paramIt = jsonObj.Find("height");
        if (paramIt == jsonObj.End()) {
            throw std::runtime_error("Parameter 'height' not found");
        }
        const int height = static_cast<int>(static_cast<const json::Number&>(paramIt->element).Value());

        paramIt = jsonObj.Find("visible");
        if (paramIt == jsonObj.End()) {
            throw std::runtime_error("Parameter 'visible' not found");
        }
        const bool visible = static_cast<const json::Boolean&>(paramIt->element).Value();

        AlignType align = AlignType::None;
        paramIt = jsonObj.Find("align");
        if (paramIt != jsonObj.End()) {
            align = strToAlign(static_cast<const json::String&>(paramIt->element).Value());
            
        }

        std::array<int, 4> margin = { 0,0,0,0 };
        paramIt = jsonObj.Find("margin");
        if (paramIt != jsonObj.End()) {
            auto v = Utils::strtoki(static_cast<const json::String&>(paramIt->element).Value());
            std::copy_n(v.begin(), 4, margin.begin());
        }

        std::array<int, 4> padding = { 0,0,0,0 };
        paramIt = jsonObj.Find("padding");
        if (paramIt != jsonObj.End()) {
            auto v = Utils::strtoki(static_cast<const json::String&>(paramIt->element).Value());
            std::copy_n(v.begin(), 4, padding.begin());
        }

        float rounding = 0.0f;
        paramIt = jsonObj.Find("rounding");
        if (paramIt != jsonObj.End()) {
            rounding = float(static_cast<const json::Number&>(paramIt->element).Value());
        }

        ctrl = createControl(type, name);
        ctrl->SetPos(posX, posY, width, height);
        ctrl->SetVisible(visible);
        ctrl->SetAlign(align);
        ctrl->SetMargin(margin[0], margin[1], margin[2], margin[3]);
        ctrl->SetPadding(padding[0], padding[1], padding[2], padding[3]);
        ctrl->SetRounding(rounding);

        switch (type)
        {
        case GUI::ControlType::Window:
            break;
        case GUI::ControlType::Panel: {
            paramIt = jsonObj.Find("bgColor");
            if (paramIt == jsonObj.End()) {
                throw std::runtime_error("Parameter 'bgColor' not found");
            }
            Panel* control = static_cast<Panel*>(ctrl.get());
            const auto c = Utils::strtokf(static_cast<const json::String&>(paramIt->element).Value());
            control->SetBgColor(ImVec4(c[0], c[1], c[2], c[3]));
        } break;
        case GUI::ControlType::Button: {
            paramIt = jsonObj.Find("text");
            if (paramIt == jsonObj.End()) {
                throw std::runtime_error("Parameter 'text' not found");
            }
            Button* control = static_cast<Button*>(ctrl.get());
            control->SetText(static_cast<const json::String&>(paramIt->element).Value());

            paramIt = jsonObj.Find("textColor");
            if (paramIt == jsonObj.End()) {
                throw std::runtime_error("Parameter 'textColor' not found");
            }
            const auto textColor = Utils::strtokf(static_cast<const json::String&>(paramIt->element).Value());
            control->SetTextColor(ImVec4(textColor[0], textColor[1], textColor[2], textColor[3]));

            paramIt = jsonObj.Find("normalColor");
            if (paramIt == jsonObj.End()) {
                throw std::runtime_error("Parameter 'normalColor' not found");
            }
            const auto normalColor = Utils::strtokf(static_cast<const json::String&>(paramIt->element).Value());
            control->SetNormalColor(ImVec4(normalColor[0], normalColor[1], normalColor[2], normalColor[3]));

            paramIt = jsonObj.Find("hoverColor");
            if (paramIt == jsonObj.End()) {
                throw std::runtime_error("Parameter 'hoverColor' not found");
            }
            const auto hoverColor = Utils::strtokf(static_cast<const json::String&>(paramIt->element).Value());
            control->SetHoverColor(ImVec4(hoverColor[0], hoverColor[1], hoverColor[2], hoverColor[3]));

            paramIt = jsonObj.Find("activeColor");
            if (paramIt == jsonObj.End()) {
                throw std::runtime_error("Parameter 'activeColor' not found");
            }
            const auto activeColor = Utils::strtokf(static_cast<const json::String&>(paramIt->element).Value());
            control->SetActiveColor(ImVec4(activeColor[0], activeColor[1], activeColor[2], activeColor[3]));
        } break;
        case GUI::ControlType::Label:
            break;
        case GUI::ControlType::TextBox:
            break;
        case GUI::ControlType::CheckBox:
            break;
        default:
            throw std::runtime_error("Unknown control type '" + std::to_string(static_cast<int>(type)) + "'");
            break;
        }

        paramIt = jsonObj.Find("controls");
        if (paramIt != jsonObj.End()) {
            const json::Array& childs = static_cast<const json::Array&>(paramIt->element);
            for (auto it = childs.Begin(); it != childs.End(); ++it) {
                const json::Object& jsonChild = *it;
                auto childCtrl = CreateControl(jsonChild);
                ctrl->AddControl(std::move(childCtrl));
            }
        }
        return ctrl;
    }

    tdControls LoadGUIFromFile(const std::string& descriptionFile)
    {
#ifdef _DEBUG
        const std::string jsonText {u8R"(
[
    {
        "type" : "panel",
        "name" : "panelMainMenu",
        "posX" : 0,
        "posY" : 0,
        "width": 300,
        "height" : 300,
        "visible" : true,
        "align" : "center",
        "rounding" : 5.0,
        "padding" : "20,20,20,20",
        "bgColor" : "0.01,0.05,0.2,1.0",
        "controls" : [
            {
                "type" : "button",
                "name" : "btnGoToGarage",
                "posX" : 0,
                "posY" : 0,
                "width": 35,
                "height" : 35,
                "visible" : true,
                "align" : "top",
                "margin" : "0,0,0,10",
                "rounding" : 5.0,
                "text" : "Создать механизм",
                "textColor" : "0.9,0.9,1.0,1.0",
                "normalColor" : "0.1,0.5,0.9,1.0",
                "hoverColor" : "0.2,0.6,1.0,1.0",
                "activeColor" : "0.0,0.4,0.8,1.0"
            },
            {
                "type" : "button",
                "name" : "btnExit",
                "posX" : 0,
                "posY" : 0,
                "width": 35,
                "height" : 35,
                "text" : "Выход",
                "visible" : true,
                "align" : "top",
                "margin" : "0,0,0,0",
                "rounding" : 5.0,
                "textColor" : "0.9,0.9,1.0,1.0",
                "normalColor" : "0.1,0.5,0.9,1.0",
                "hoverColor" : "0.2,0.6,1.0,1.0",
                "activeColor" : "0.0,0.4,0.8,1.0"           
            }
        ]
    }
]
)"};
#else
        const std::string jsonText = Utils::ReadFile(descriptionFile);
#endif
        std::istringstream istr(jsonText);
        json::Array jsonControls;
        json::Reader::Read(jsonControls, istr);
        tdControls res;

        for (auto it = jsonControls.Begin(); it != jsonControls.End(); ++it) {
            const json::Object& jsonObj = *it;
            auto ctrl = CreateControl(jsonObj);
            res.push_back(std::move(ctrl));
        }

        return res;
    }
}