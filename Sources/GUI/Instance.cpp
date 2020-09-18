#include "Instance.h"
#include "SettingsManager.h"
#include "EventManager.h"
#include "EventType.h"
#include "GUISettings.h"
#include "ControlFactory.h"
#include "Utils.h"
#include "AlignHelper.h"
#include "JsonCast.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "SDL.h"
#include "elements.h"
#include <stdexcept>
#include <memory>

namespace GUI
{

    Instance::Instance(SDL_Window* window, void* glContext, const std::string& configFile)
        : settingsManager_(configFile, GetDefaultSettings(), true)
    {
        window_ = window;
        ImGui::CreateContext();
        ImGui_ImplSDL2_InitForOpenGL(window_, glContext);
        ImGui_ImplOpenGL2_Init();
        EventManager::PushObserver(this, EventManager::EventType::WindowResize);
    }

    Instance::~Instance()
    {
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void Instance::ProcessFrame()
    {
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(window_);
        ImGui::NewFrame();

        ImGuiStyle& style = ImGui::GetStyle();
        const auto prevPadding = style.WindowPadding;
        const auto prevBorder = style.WindowBorderSize;
        style.WindowPadding = zeroVec2;
        style.WindowBorderSize = 0;
        ImGui::SetNextWindowPos(zeroVec2, 0, zeroVec2);
        ImGui::SetNextWindowSize(windowSize_);
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
        style.WindowBorderSize = prevBorder;

        for (const auto& control : controls_) {
            if (control->IsVisible())
                control->Render();
        }

        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }

    void Instance::EventHandling(const EventManager::IEvent& event)
    {
        if (event.GetType() == EventManager::EventType::WindowResize)
        {
            int winWidth;
            int winHeight;
            SDL_GL_GetDrawableSize(window_, &winWidth, &winHeight);
            windowSize_ = ImVec2((float)winWidth, (float)winHeight);
            AlignHelper::UpdateControlsPosition(controls_, 0, 0, winWidth, winHeight);
        }
    }

    void Instance::LoadGUI(const std::string& jsonFile)
    {
        const json::Object jsonObj = JsonCast::loadFromFile(jsonFile);
        const auto fontFile = static_cast<const json::String&>(jsonObj["FontFile"]).Value();
        const float fontSize = float(static_cast<const json::Number&>(jsonObj["FontSize"]).Value());
        int val = int(static_cast<const json::Number&>(jsonObj["FontHinting"]).Value());
        const ImGuiFreeType::RasterizerFlags fontHinting = static_cast<ImGuiFreeType::RasterizerFlags>(val);

        if (!fontFile.empty()) {
            SetFont(Utils::ExtractPath(settingsManager_.GetConfigFileName()) + "/" + fontFile, fontSize, fontHinting);
        }

        controls_ = CreateControls(jsonObj["controls"]);

        int winWidth;
        int winHeight;
        SDL_GL_GetDrawableSize(window_, &winWidth, &winHeight);
        windowSize_ = ImVec2((float)winWidth, (float)winHeight);
        AlignHelper::UpdateControlsPosition(controls_, 0, 0, winWidth, winHeight);
    }

    void Instance::SetFont(const std::string& filename, float sizeInPixels, ImGuiFreeType::RasterizerFlags hintType)
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
            ImGuiFreeType::BuildFontAtlas(io.Fonts, hintType);
        }
        if (!font->IsLoaded()) {
            throw std::runtime_error("Can't load font file '" + filename + "'");
        }
    }

}