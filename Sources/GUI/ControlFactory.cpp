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

        switch (type)
        {
        case GUI::ControlType::Window:
            break;
        case GUI::ControlType::Panel:
            break;
        case GUI::ControlType::Button:
            ctrl = Utils::unique_ptr_cast<Button>(createControl(type, name));
            break;
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

        ctrl->SetPos(posX, posY, width, height);
        ctrl->SetVisible(visible);

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
    }

    tdControls LoadGUIFromFile(const std::string& descriptionFile)
    {
        const std::string jsonText = Utils::ReadFile(descriptionFile);
        std::istringstream istr(jsonText);
        json::Reader r;
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