
#include "Graphics.h"
#include "SDL.h"
#include "SDL_opengl.h"
#include "SettingsManager.h"
#include "GraphicsSettings.h"
#include "Utils.h"
#include <stdexcept>
#include <memory>

namespace Graphics 
{
    SDL_Window* window_ = nullptr;
    SDL_GLContext glContext_ = nullptr;
    std::unique_ptr<SettingsManager> settingsManager_;

    LIB_API void Init(const std::string& configFile)
    {
        settingsManager_ = std::make_unique<SettingsManager>(configFile, GetDefaultSettings(), true);

        int res = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
        if (res != 0) {
            throw std::runtime_error("Can't init SDL (" + std::string(SDL_GetError()) + ")");
        }

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, settingsManager_->GetPropertyAsInteger(Setting::SetAttribute_DOUBLEBUFFER));
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, settingsManager_->GetPropertyAsInteger(Setting::SetAttribute_DEPTH_SIZE));
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, settingsManager_->GetPropertyAsInteger(Setting::SetAttribute_STENCIL_SIZE));
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, settingsManager_->GetPropertyAsInteger(Setting::SetAttribute_CONTEXT_MAJOR_VERSION));
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, settingsManager_->GetPropertyAsInteger(Setting::SetAttribute_CONTEXT_MINOR_VERSION));
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, settingsManager_->GetPropertyAsInteger(Setting::SetAttribute_ACCELERATED_VISUAL));
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, settingsManager_->GetPropertyAsString(Setting::HintRenderScaleQuality).c_str());

        const bool fullscreen = settingsManager_->GetPropertyAsBool(Setting::WindowIsFullscreen);

        window_ = SDL_CreateWindow(settingsManager_->GetPropertyAsString(Setting::WindowTitleText).c_str(), 
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            settingsManager_->GetPropertyAsInteger(Setting::WindowWidth),
            settingsManager_->GetPropertyAsInteger(Setting::WindowHeight),
            SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | (fullscreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE));
        if (window_ == nullptr) {
            throw std::runtime_error("Can't create window (" + std::string(SDL_GetError()) + ")");
        }

        glContext_ = SDL_GL_CreateContext(window_);
        if (glContext_ == nullptr) {
            throw std::runtime_error("Can't create OpenGL context (" + std::string(SDL_GetError()) + ")");
        }
        SDL_GL_MakeCurrent(window_, glContext_);

        if (settingsManager_->GetPropertyAsBool(Setting::Enable_GL_BLEND)) glEnable(GL_BLEND); else glDisable(GL_BLEND);
        if (settingsManager_->GetPropertyAsBool(Setting::Enable_GL_TEXTURE_2D)) glEnable(GL_TEXTURE_2D); else glDisable(GL_TEXTURE_2D);
        if (settingsManager_->GetPropertyAsBool(Setting::Enable_GL_LINE_SMOOTH)) glEnable(GL_LINE_SMOOTH); else glDisable(GL_LINE_SMOOTH);
        if (settingsManager_->GetPropertyAsBool(Setting::Enable_GL_DEPTH_TEST)) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
        if (settingsManager_->GetPropertyAsBool(Setting::Enable_GL_CULL_FACE)) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
        if (settingsManager_->GetPropertyAsBool(Setting::Enable_GL_MULTISAMPLE)) glEnable(GL_MULTISAMPLE); else glDisable(GL_MULTISAMPLE);
        if (settingsManager_->GetPropertyAsBool(Setting::Enable_GL_POLYGON_SMOOTH)) glEnable(GL_POLYGON_SMOOTH); else glDisable(GL_POLYGON_SMOOTH);

        glHint(GL_POINT_SMOOTH_HINT, settingsManager_->GetPropertyAsInteger(Setting::Hint_GL_POINT_SMOOTH_HINT));
        glHint(GL_LINE_SMOOTH_HINT, settingsManager_->GetPropertyAsInteger(Setting::Hint_GL_LINE_SMOOTH_HINT));
        glBlendFunc(GL_SRC_ALPHA, settingsManager_->GetPropertyAsInteger(Setting::BlendFunc_GL_SRC_ALPHA));

        SetVSync(settingsManager_->GetPropertyAsBool(Setting::WindowVSyncEnable));
        const auto clearColor = Utils::stocolor(settingsManager_->GetPropertyAsString(Setting::ClearColor));
        SetClearColor(clearColor[0], clearColor[1], clearColor[2], 1.0f);
    }

    LIB_API void ClearFrame()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    LIB_API void SwapFrame()
    {
        SDL_GL_SwapWindow(window_);
    }

    LIB_API void SetVSync(bool enable)
    {
        SDL_GL_SetSwapInterval(enable);
    }

    LIB_API void SetClearColor(float red, float green, float blue, float alpha)
    {
        glClearColor(red, green, blue, alpha);
    }

    LIB_API SDL_Window* GetCurrentWindow()
    {
        return window_;
    }

    LIB_API void* GetOpenGLContext()
    {
        return glContext_;
    }

}