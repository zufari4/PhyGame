#pragma once
#include "SettingsManager.h"
#include "BaseControl.h"
#include "IEventObserver.h"
#include "SDL.h"
#include "imgui.h"
#include <string>

namespace GUI
{
    class Instance: public EventManager::IEventObserver
    {
    public:
        Instance(SDL_Window* window, void* glContext, const std::string& configFile);
        ~Instance();
        void ProcessFrame();
        void EventHandling(const EventManager::IEvent& event) override;
        void LoadGUI(const std::string& jsonFile);
    private:
        SDL_Window* window_ = nullptr;
        SettingsManager settingsManager_;
        tdControls controls_;
        ImVec2 windowSize_;
    };
}