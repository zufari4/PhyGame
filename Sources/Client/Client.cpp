#include "Graphics.h"
#include "Client.h"
#include "EventFactory.h"
#include "EventManager.h"
#include "GUI.h"
#include "Utils.h"
#include "ClientSettings.h"

Client::Client()
    : settingsManager_(GetConfigFileName(), GetDefaultClientSettings(), true)
{

}

bool Client::Init()
{
    const auto& configFile = GetConfigFileName();
    Graphics::Init(configFile);
    GUI::Init(Graphics::GetCurrentWindow(), Graphics::GetOpenGLContext(), configFile);
    GUI::LoadGUI(GetDataDir()+ "/" + settingsManager_.GetPropertyAsString(ClientSetting::GUIMainMenuFile));
    EventManager::PushObserver(this, EventManager::EventType::Quit);
    EventManager::PushObserver(this, EventManager::EventType::ButtonClick);
    workFlag_ = true;
    return true;
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

        }
        break;
    }
}

std::string Client::GetDataDir()
{
    return Utils::GetAppDataPath() + "\\PhyGame";
}

std::string Client::GetConfigFileName()
{
    return GetDataDir() + "\\settings.ini";
}
