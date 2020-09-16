#pragma once
#include "SettingsManager.h"
#include "BaseControl.h"
#include "IEventObserver.h"
#include "SDL.h"
#include "imgui.h"
#include "imgui_freetype.h"
#include <string>
#include <memory>

namespace GUI
{
    class Instance: public EventManager::IEventObserver
    {
    public:
        Instance(SDL_Window* window, void* glContext, const std::string& configFile);
        ~Instance();
        void ProcessFrame();
        void EventHandling(const EventManager::IEvent& event) override;
    private:
        SDL_Window* window_ = nullptr;
        float current_font_size_ = 1.0;
        const ImVec2 imVec2Zero = ImVec2(0, 0);
        std::unique_ptr<SettingsManager> settingsManager_;
        tdControls controls_;
        ImVec2 windowSize_;

        void SetFont(const std::string& filename, float sizeInPixels, ImGuiFreeType::RasterizerFlags hintType);
    };
}