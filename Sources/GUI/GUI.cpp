#include "GUI.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_freetype.h"
#include "SDL.h"
#include "SettingsManager.h"
#include "GUISettings.h"
#include "ControlFactory.h"

#include <stdexcept>
#include <memory>

namespace GUI
{
    using tdControls = std::vector<std::unique_ptr<BaseControl>>;

    SDL_Window* window_ = nullptr;
    float current_font_size_ = 1.0;
    const ImVec2 imVec2Zero = ImVec2(0, 0);
    std::unique_ptr<SettingsManager> settingsManager_;
    tdControls controls_;
    std::string resourcesPath_;

    tdControls LoadGUIFromFile(const std::string& descriptionFile);
    void SetFont(const std::string& filename, float sizeInPixels);

    LIB_API void GUI::Init(SDL_Window* window, const std::string& configFile, const std::string& resourcesPath)
    {
        window_ = window;
        resourcesPath_ = resourcesPath;
        settingsManager_ = std::make_unique<SettingsManager>(configFile, GetDefaultSettings(), true);
        ImGui_ImplSdlGL2_Init(window);
        current_font_size_ = ImGui::GetFontSize();
        controls_ = LoadGUIFromFile(settingsManager_->GetPropertyAsString(Setting::DescriptionFile));
        const auto fontFile = settingsManager_->GetPropertyAsString(Setting::FontFile);
        if (!fontFile.empty()) SetFont(resourcesPath + "\\" + fontFile, settingsManager_->GetPropertyAsFloat(Setting::FontSize));
    }

    tdControls LoadGUIFromFile(const std::string& descriptionFile)
    {
        tdControls res;
        std::unique_ptr<Button> ctrl = createControlButton("btnGoToGarage");
        ctrl->SetPos(10, 10, 20, 100);
        ctrl->SetText("Привет");
        res.push_back(std::move(ctrl));
        return res;
    }

    LIB_API void ProcessFrame()
    {
        ImGui_ImplSdlGL2_NewFrame(window_);
        ImGuiStyle* style = &ImGui::GetStyle();
        const auto prevPadding = style->WindowPadding;
        style->WindowPadding = ImVec2(0, 0);
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
        style->WindowPadding = prevPadding;

        ImGui::SetCursorPos(ImVec2(20, 20));               
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.5f, 0.9f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.6f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.4f, 0.8f, 1.0f));
        ImGui::Button(u8"Привет мир!", ImVec2(200, 35));
        ImGui::PopStyleColor(3);

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
            ImGuiFreeType::BuildFontAtlas(io.Fonts, ImGuiFreeType::RasterizerFlags::NoHinting);
            current_font_size_ = sizeInPixels;
        }
        if (!font->IsLoaded()) {
            throw std::runtime_error("Can't load font file '" + filename + "'");
        }
    }

}