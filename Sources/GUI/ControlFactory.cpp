#include "ControlFactory.h"
#include "ControlTypes.h"
#include "Utils.h"
#include "AlignType.h"
#include "FontManager.h"
#include "Button.h"
#include "Panel.h"
#include "Label.h"
#include "TextAlign.h"
#include "elements.h"


namespace GUI
{
    std::unique_ptr<BaseControl> createControl(ControlType type, const std::string& name, BaseControl* parent /*= nullptr*/)
    {
        std::unique_ptr<BaseControl> ctrl;

        switch (type)
        {
        case ControlType::Window:
            break;
        case ControlType::Panel:
            ctrl = std::make_unique<Panel>(name, parent);
            break;
        case ControlType::Button:
            ctrl = std::make_unique<Button>(name, parent);
            break;
        case ControlType::Label:
            ctrl = std::make_unique<Label>(name, parent);
            break;
        case ControlType::TextBox:
            break;
        case ControlType::CheckBox:
            break;
        default:
            break;
        }

        return ctrl;
    }

    std::unique_ptr<BaseControl> CreateControl(const std::string& resourceDirectory, const json::Object jsonObj)
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
        
        std::string fontFile;
        paramIt = jsonObj.Find("fontFile");
        if (paramIt != jsonObj.End()) {
            fontFile = static_cast<const json::String&>(paramIt->element).Value();
        }

        float fontSize = 1;
        paramIt = jsonObj.Find("fontSize");
        if (paramIt != jsonObj.End()) {
            fontSize = float(static_cast<const json::Number&>(paramIt->element).Value());
        }

        unsigned fontHinting = 0;
        paramIt = jsonObj.Find("fontHinting");
        if (paramIt != jsonObj.End()) {
            fontHinting = unsigned(static_cast<const json::Number&>(paramIt->element).Value());
        }

        std::string fileActivate;
        paramIt = jsonObj.Find("fileActivate");
        if (paramIt != jsonObj.End()) {
            fileActivate = static_cast<const json::String&>(paramIt->element).Value();
        }

        ctrl = createControl(type, name);
        ctrl->SetPos(posX, posY, width, height);
        ctrl->SetVisible(visible);
        ctrl->SetAlign(align);
        ctrl->SetMargin(margin[0], margin[1], margin[2], margin[3]);
        ctrl->SetPadding(padding[0], padding[1], padding[2], padding[3]);
        ctrl->SetRounding(rounding);
        if (!fontFile.empty()) {
            ctrl->SetFont(FontManager::CreateFont(resourceDirectory + "/" + fontFile, fontSize, fontHinting));
        }
        if (!fileActivate.empty()) {
            ctrl->SetFileActivate(fileActivate);
        }

        switch (type)
        {
        case ControlType::Window:
            break;
        case ControlType::Panel: {
            paramIt = jsonObj.Find("bgColor");
            if (paramIt == jsonObj.End()) {
                throw std::runtime_error("Parameter 'bgColor' not found");
            }
            Panel* control = static_cast<Panel*>(ctrl.get());
            const auto c = Utils::strtokf(static_cast<const json::String&>(paramIt->element).Value());
            control->SetBgColor(ImVec4(c[0], c[1], c[2], c[3]));
        } break;
        case ControlType::Button: {
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
        case ControlType::Label: {
            Label* control = static_cast<Label*>(ctrl.get());
            paramIt = jsonObj.Find("text");
            if (paramIt != jsonObj.End()) {
                control->SetText(static_cast<const json::String&>(paramIt->element).Value());
            }
            paramIt = jsonObj.Find("bgColor");
            if (paramIt != jsonObj.End()) {
                const auto c = Utils::strtokf(static_cast<const json::String&>(paramIt->element).Value());
                control->SetBackgroundColor(ImVec4(c[0], c[1], c[2], c[3]));
            }
            paramIt = jsonObj.Find("textColor");
            if (paramIt != jsonObj.End()) {
                const auto c = Utils::strtokf(static_cast<const json::String&>(paramIt->element).Value());
                control->SetTextColor(ImVec4(c[0], c[1], c[2], c[3]));
            }
            paramIt = jsonObj.Find("textAlign");
            if (paramIt != jsonObj.End()) {
                const auto align = strToTextAlign(static_cast<const json::String&>(paramIt->element).Value());
                control->SetTextAlign(align);
            }
        } break;
        case ControlType::TextBox:
            break;
        case ControlType::CheckBox:
            break;
        default:
            throw std::runtime_error("Unknown control type '" + std::to_string(static_cast<int>(type)) + "'");
            break;
        }

        paramIt = jsonObj.Find("controls");
        if (paramIt != jsonObj.End()) {
            auto childs = CreateControls(resourceDirectory, paramIt->element);
            for (auto& it : childs) {
                ctrl->AddControl(std::move(it));
            }
        }
        return ctrl;
    }

    tdControls CreateControls(const std::string& resourceDirectory, const json::Array& controls)
    {
        tdControls res;

        for (auto it = controls.Begin(); it != controls.End(); ++it) {
            const json::Object& jsonObj = *it;
            auto ctrl = CreateControl(resourceDirectory, jsonObj);
            res.push_back(std::move(ctrl));
        }

        return res;
    }
}