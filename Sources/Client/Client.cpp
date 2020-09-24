#include "Graphics.h"
#include "Client.h"
#include "EventManager.h"
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
        Graphics::SetCamera2D(0, 0);
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

void Client::EventHandling(const EventManager::BaseEvent& event)
{
    try
    {
        switch (event.type)
        {
        case EventManager::EventType::Quit:
            workFlag_ = false;
            break;
        case EventManager::EventType::ButtonClick:
            const EventManager::EventButtonClick& ev = (const EventManager::EventButtonClick&)event;
            if (ev.sender == "btnExit") {
                workFlag_ = false;
            }
            else if (ev.sender == "createMechanizm") {
                state_ = GameState::SelectToolForMechanizm;
            }
            else if (ev.sender == "setShape") {
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
