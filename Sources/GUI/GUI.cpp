#include "GUI.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_freetype.h"
#include "SDL.h"
#include "SettingsManager.h"
#include "GUISettings.h"

#include <stdexcept>
#include <memory>

namespace GUI
{
    SDL_Window* window_ = nullptr;
    float current_font_size_ = 1.0;
    std::unique_ptr<SettingsManager> settingsManager_;


    LIB_API void GUI::Init(SDL_Window* window, const std::string& configFile)
    {
        settingsManager_ = std::make_unique<SettingsManager>(configFile, GetDefaultSettings(), true);

        window_ = window;
        ImGui_ImplSdlGL2_Init(window);
        current_font_size_ = ImGui::GetFontSize();
    }
}