#include "Graphics.h"
#include "Client.h"
#include "EventFactory.h"
#include "EventManager.h"
#include "GUI.h"
#include "Utils.h"
#include "ClientSettings.h"
#include "ErrorWindow.h"
#include "EventMouseUp.h"

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
        GUI::Init(Graphics::GetCurrentWindow(), Graphics::GetOpenGLContext(), configFileName);
        GUI::LoadGUI(GetDataDir() + "/" + settingsManager_->GetPropertyAsString(ClientSetting::GUIMainMenuFile));
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
            if (event.GetSender() == "btnExit") {
                workFlag_ = false;
            }
            if (event.GetSender() == "setShape") {
                state_ = GameState::SetShape;
                shapeConstructor_ = std::make_unique<ShapeConstructor>();

            }
            if (event.GetSender() == "createMechanizm") {
                GUI::LoadGUI(GetDataDir() + "/" + settingsManager_->GetPropertyAsString(ClientSetting::GUICreateMechanizmFile));
                state_ = GameState::SelectToolForMechanizm;
            }
            break;

        case EventManager::EventType::MouseUp:
            if (state_ == GameState::SetShape) {
                const EventManager::MouseUpParams* params = static_cast<const EventManager::MouseUpParams*>(event.GetParams());
                if (params->button == 0) {
                    shapeConstructor_->AddPoint((float)params->x, (float)params->y);
                }
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
