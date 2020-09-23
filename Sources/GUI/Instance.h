#pragma once
#include "SettingsManager.h"
#include "BaseControl.h"
#include "IEventObserver.h"
#include "SDL.h"
#include "imgui.h"
#include <string>
#include <mutex>

namespace GUI
{
    class Instance: public EventManager::IEventObserver
    {
    public:
        Instance(SDL_Window* window, void* glContext, const std::string& configFile, const std::string& resourceDirectory);
        ~Instance();
        void ProcessFrame();
        void EventHandling(const EventManager::IEvent& event) override;
        void LoadGUI(const std::string& jsonFile);
        const std::string& GetResourceDirectory() const;
    private:
        SDL_Window* window_ = nullptr;
        SettingsManager settingsManager_;
        tdControls controls_;
        ImVec2 windowSize_;
        std::string resourceDirectory_;
        std::mutex controlsMutex_;
    };
}