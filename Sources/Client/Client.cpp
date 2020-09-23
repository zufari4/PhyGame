#include "Graphics.h"
#include "Client.h"
#include "EventManager.h"
#include "EventType.h"
#include "GUI.h"
#include "Utils.h"
#include "ClientSettings.h"
#include "ErrorWindow.h"
#include "EventMouseUp.h"
#include "EventButtonClick.h"

Client::Client()
    : state_(GameState::Undefined)
{

}

bool Client::Init()
{
    try
    {
        state_ = GameState::Init;
        const auto configFileName = GetConfigFileName();
        settingsManager_ = std::make_unique<SettingsManager>(configFileName, GetDefaultClientSettings(), true);
        Graphics::Init(configFileName);
        GUI::Init(Graphics::GetCurrentWindow(), Graphics::GetOpenGLContext(), configFileName, GetDataDir());
        GUI::LoadGUI(GetDataDir() + "/" + settingsManager_->GetPropertyAsString(ClientSetting::GUIMainFile));
        EventManager::PushObserver(this, EventManager::EventType::Quit);
        EventManager::PushObserver(this, EventManager::EventType::ButtonClick);
        EventManager::PushObserver(this, EventManager::EventType::MouseUp);
        int frameWidth = Graphics::GetFrameWidth();
        int frameHeight = Graphics::GetFrameHeight();
        Graphics::SetCamera2D(frameWidth / 2.0f, frameHeight / 2.0f);
        workFlag_ = true;
        state_ = GameState::MainMenu;
        return true;
    }
    catch (const std::exception& e)
    {
        ShowErroWindow(e.what());
        return false;
    }
}

void Client::Run()
{
    while (workFlag_)
    {
        EventManager::ProcessEvents();
        Graphics::ClearFrame();
        switch (state_)
        {
        case GameState::SetShape:
            if (shapeConstructor_) shapeConstructor_->Draw();
            break;
        }
        GUI::ProcessFrame();
        Graphics::SwapFrame();
    }
}

void Client::Free()
{
    GUI::Free();
}

void Client::EventHandling(const EventManager::IEvent& event)
{
    try
    {
        switch (event.GetType())
        {
        case EventManager::EventType::Quit:
            workFlag_ = false;
            break;
        case EventManager::EventType::ButtonClick:
            const EventManager::ButtonClickParam* params = (const EventManager::ButtonClickParam*)event.GetParams();
            if (params->sender == "btnExit") {
                workFlag_ = false;
            }
            else if (params->sender == "createMechanizm") {
                state_ = GameState::SelectToolForMechanizm;
            }
            else if (params->sender == "setShape") {
                state_ = GameState::SetShape;
                shapeConstructor_ = std::make_unique<ShapeConstructor>();

            }
            break;
        }
    }
    catch (const std::exception& e)
    {
        ShowErroWindow(e.what());
    }
}

std::string Client::GetDataDir()
{
    return Utils::GetCurrentDirectory() + "/../../Resources";
}

std::string Client::GetConfigFileName()
{
    return GetDataDir() + "/settings.ini";
}
