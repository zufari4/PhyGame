#include "GUI.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_freetype.h"
#include "SDL.h"
#include "SettingsManager.h"
#include "GUISettings.h"
#include "ControlFactory.h"
#include "Utils.h"

#include <stdexcept>
#include <memory>

namespace GUI
{
    

    SDL_Window* window_ = nullptr;
    float current_font_size_ = 1.0;
    const ImVec2 imVec2Zero = ImVec2(0, 0);
    std::unique_ptr<SettingsManager> settingsManager_;
    tdControls controls_;
    
    void SetFont(const std::string& filename, float sizeInPixels);

    LIB_API void GUI::Init(SDL_Window* window, const std::string& configFile)
    {
        window_ = window;
        settingsManager_ = std::make_unique<SettingsManager>(configFile, GetDefaultSettings(), true);
        ImGui_ImplSdlGL2_Init(window);
        controls_ = LoadGUIFromFile(Utils::ExtractPath(configFile) + "\\" + settingsManager_->GetPropertyAsString(Setting::DescriptionFile));
        const auto fontFile = settingsManager_->GetPropertyAsString(Setting::FontFile);
        if (!fontFile.empty()) SetFont(Utils::ExtractPath(configFile) + "\\" + fontFile, settingsManager_->GetPropertyAsFloat(Setting::FontSize));
        current_font_size_ = ImGui::GetFontSize();
    }

    LIB_API void ProcessFrame()
    {
        ImGui_ImplSdlGL2_NewFrame(window_);
        ImGuiStyle& style = ImGui::GetStyle();
        const auto prevPadding = style.WindowPadding;
        style.WindowPadding = ImVec2(0, 0);
        ImGui::Begin("", nullptr, imVec2Zero, 0.0f,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoSavedSettings |
            //ImGuiWindowFlags_NoInputs |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoBringToFrontOnFocus
            
        );
        style.WindowPadding = prevPadding;

        for (const auto& control : controls_) {
            control->Render();
        }

        ImGui::End();
        ImGui::Render();
    }

    void SetFont(const std::string& filename, float sizeInPixels)
    {
        if (filename.empty()) {
            return;
        }
        ImGuiIO& io = ImGui::GetIO();
        ImFont* font = io.Fonts->AddFontFromFileTTF(filename.c_str(), sizeInPixels, NULL, io.Fonts->GetGlyphRangesCyrillic());
        if (font == NULL) {
            throw std::runtime_error("Can't load font file '" + filename + "'");
        }
        else {
            ImGuiFreeType::RasterizerFlags hintType = static_cast<ImGuiFreeType::RasterizerFlags>(settingsManager_->GetPropertyAsInteger(Setting::FontHinting));
            ImGuiFreeType::BuildFontAtlas(io.Fonts, hintType);
            current_font_size_ = sizeInPixels;
        }
        if (!font->IsLoaded()) {
            throw std::runtime_error("Can't load font file '" + filename + "'");
        }
    }

}