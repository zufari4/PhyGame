#include "ControlFactory.h"
#include "ControlTypes.h"
#include "Button.h"
#include "Utils.h"
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
        const ControlType type = static_cast<ControlType>(static_cast<const json::Number&>(paramIt->element).Value());

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

        ctrl = createControl(type, name);
        ctrl->SetPos(posX, posY, width, height);
        ctrl->SetVisible(visible);

        switch (type)
        {
        case GUI::ControlType::Window:
            break;
        case GUI::ControlType::Panel:
            break;
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
        if (paramIt == jsonObj.End()) {
            throw std::runtime_error("Parameter 'controls' not found");
        }
        const json::Array& childs = static_cast<const json::Array&>(paramIt->element);
        for (auto it = childs.Begin(); it != childs.End(); ++it) {
            const json::Object& jsonChild = *it;
            auto childCtrl = CreateControl(jsonChild);
            ctrl->AddControl(std::move(childCtrl));
        }

        return ctrl;
    }

    tdControls LoadGUIFromFile(const std::string& descriptionFile)
    {
        const std::string jsonText = Utils::ReadFile(descriptionFile);
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