#include "Graphics.h"
#include "Client.h"
#include "EventFactory.h"
#include "EventManager.h"
#include "GUI.h"
#include "Utils.h"
#include "ClientSettings.h"
#include "ErrorWindow.h"

Client::Client()
{

}

bool Client::Init()
{
    try
    {
        const auto configFileName = GetConfigFileName();
        settingsManager_ = std::make_unique<SettingsManager>(configFileName, GetDefaultClientSettings(), true);
        Graphics::Init(configFileName);
        GUI::Init(Graphics::GetCurrentWindow(), Graphics::GetOpenGLContext(), configFileName);
        GUI::LoadGUI(GetDataDir() + "/" + settingsManager_->GetPropertyAsString(ClientSetting::GUIMainMenuFile));
        EventManager::PushObserver(this, EventManager::EventType::Quit);
        EventManager::PushObserver(this, EventManager::EventType::ButtonClick);
        workFlag_ = true;
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
            if (event.GetSender() == "btnExit") {
                workFlag_ = false;
            }
            if (event.GetSender() == "createMechanizm") {
                GUI::LoadGUI(GetDataDir() + "/" + settingsManager_->GetPropertyAsString(ClientSetting::GUICreateMechanizmFile));
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
