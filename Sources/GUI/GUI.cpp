#include "GUI.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
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

    LIB_API void GUI::Init(SDL_Window* window, void* glContext, const std::string& configFile)
    {
        window_ = window;
        settingsManager_ = std::make_unique<SettingsManager>(configFile, GetDefaultSettings(), true);
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForOpenGL(window_, glContext);
        ImGui_ImplOpenGL2_Init();

        controls_ = LoadGUIFromFile(Utils::ExtractPath(configFile) + "\\" + settingsManager_->GetPropertyAsString(Setting::DescriptionFile));
        const auto fontFile = settingsManager_->GetPropertyAsString(Setting::FontFile);
        if (!fontFile.empty()) SetFont(Utils::ExtractPath(configFile) + "\\" + fontFile, settingsManager_->GetPropertyAsFloat(Setting::FontSize));
        current_font_size_ = ImGui::GetFontSize();
    }

    LIB_API void Free()
    {
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    LIB_API void ProcessFrame()
    {
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window_);
        ImGui::NewFrame();

        ImGuiStyle& style = ImGui::GetStyle();
        const auto prevPadding = style.WindowPadding;
        style.WindowPadding = ImVec2(0, 0);
        ImGui::Begin("backgroundWindow", nullptr, 
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoBackground
        );
        style.WindowPadding = prevPadding;

        for (const auto& control : controls_) {
            if (control->IsVisible())
                control->Render();
        }

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
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