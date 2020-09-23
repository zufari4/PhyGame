#include "Instance.h"
#include "SettingsManager.h"
#include "EventManager.h"
#include "EventType.h"
#include "GUISettings.h"
#include "ControlFactory.h"
#include "Utils.h"
#include "AlignHelper.h"
#include "JsonCast.h"
#include "EventButtonClick.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "SDL.h"
#include "elements.h"
#include <stdexcept>
#include <memory>
#include <mutex>

namespace GUI
{

    Instance::Instance(SDL_Window* window, void* glContext, const std::string& configFile, const std::string& resourceDirectory)
        : settingsManager_(configFile, GetDefaultSettings(), true)
        , window_(window)
        , resourceDirectory_(resourceDirectory)
    {
        ImGui::CreateContext();
        ImGui_ImplSDL2_InitForOpenGL(window_, glContext);
        ImGui_ImplOpenGL2_Init();
        EventManager::PushObserver(this, EventManager::EventType::WindowResize);
        EventManager::PushObserver(this, EventManager::EventType::ButtonClick);
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
        {
            std::unique_lock<std::mutex> lock(controlsMutex_, std::try_to_lock);
            if (lock.owns_lock()) {
                for (const auto& control : controls_) {
                    if (control->IsVisible())
                        control->Render();
                }
            }
        }
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }

    void Instance::EventHandling(const EventManager::IEvent& event)
    {
        if (event.GetType() == EventManager::EventType::WindowResize) {
            int winWidth;
            int winHeight;
            SDL_GL_GetDrawableSize(window_, &winWidth, &winHeight);
            windowSize_ = ImVec2((float)winWidth, (float)winHeight);
            std::lock_guard<std::mutex> g(controlsMutex_);
            AlignHelper::UpdateControlsPosition(controls_, 0, 0, winWidth, winHeight);
        }
        else if (event.GetType() == EventManager::EventType::ButtonClick) {
            const EventManager::ButtonClickParam* params = (const EventManager::ButtonClickParam*)event.GetParams();
            if (!params->fileActive.empty()) {
                LoadGUI(resourceDirectory_ + "/" + params->fileActive);
            }
        }
    }

    void Instance::LoadGUI(const std::string& jsonFile)
    {
        std::lock_guard<std::mutex> g(controlsMutex_);
        const json::Object jsonObj = JsonCast::loadFromFile(jsonFile);
        controls_ = CreateControls(resourceDirectory_, jsonObj["controls"]);

        int winWidth;
        int winHeight;
        SDL_GL_GetDrawableSize(window_, &winWidth, &winHeight);
        windowSize_ = ImVec2((float)winWidth, (float)winHeight);
        AlignHelper::UpdateControlsPosition(controls_, 0, 0, winWidth, winHeight);
    }

    const std::string& Instance::GetResourceDirectory() const
    {
        return resourceDirectory_;
    }

}