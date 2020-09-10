#include "GraphicsSettings.h"

namespace Graphics
{
    const SettingsManager::tdProperties& GetDefaultSettings()
    {
        static const SettingsManager::tdProperties defSettings =
        {
            { Graphics::Setting::WindowTitleText, {"Window",  "TitleText", ""} },
            { Graphics::Setting::WindowWidth     , {"Window",  "Width", "1024"} },
            { Graphics::Setting::WindowHeight     , {"Window",  "Height", "768"} },
            { Graphics::Setting::WindowIsFullscreen     , {"Window",  "IsFullscreen", "False"} },
            { Graphics::Setting::WindowVSyncEnable     , {"Window",  "VSyncEnable", "True"} },
            { Graphics::Setting::HintRenderScaleQuality     , {"OpenGL",  "VSyncEnable", "\"1\""} },
            { Graphics::Setting::BlendFunc_GL_SRC_ALPHA     , {"OpenGL",  "BlendFunc_GL_SRC_ALPHA", "771"} },
            { Graphics::Setting::Enable_GL_CULL_FACE     , {"OpenGL",  "Disable_GL_CULL_FACE", "False"} },
            { Graphics::Setting::Enable_GL_DEPTH_TEST     , {"OpenGL",  "Disable_GL_DEPTH_TEST", "False"} },
            { Graphics::Setting::Enable_GL_MULTISAMPLE     , {"OpenGL",  "Disable_GL_MULTISAMPLE", "False"} },
            { Graphics::Setting::Enable_GL_POLYGON_SMOOTH     , {"OpenGL",  "Disable_GL_POLYGON_SMOOTH", "False"} },
            { Graphics::Setting::Enable_GL_BLEND     , {"OpenGL",  "Enable_GL_BLEND", "True"} },
            { Graphics::Setting::Enable_GL_LINE_SMOOTH     , {"OpenGL",  "Enable_GL_LINE_SMOOTH", "True"} },
            { Graphics::Setting::Enable_GL_TEXTURE_2D     , {"OpenGL",  "Enable_GL_TEXTURE_2D", "True"} },
            { Graphics::Setting::Hint_GL_LINE_SMOOTH_HINT     , {"OpenGL",  "Hint_GL_LINE_SMOOTH_HINT", "4353"} },
            { Graphics::Setting::Hint_GL_POINT_SMOOTH_HINT     , {"OpenGL",  "Hint_GL_POINT_SMOOTH_HINT", "4353"} },
            { Graphics::Setting::SetAttribute_ACCELERATED_VISUAL     , {"OpenGL",  "SetAttribute_ACCELERATED_VISUAL", "1"} },
            { Graphics::Setting::SetAttribute_CONTEXT_MAJOR_VERSION     , {"OpenGL",  "SetAttribute_CONTEXT_MAJOR_VERSION", "2"} },
            { Graphics::Setting::SetAttribute_CONTEXT_MINOR_VERSION     , {"OpenGL",  "SetAttribute_CONTEXT_MINOR_VERSION", "2"} },
            { Graphics::Setting::SetAttribute_DEPTH_SIZE     , {"OpenGL",  "SetAttribute_DEPTH_SIZE", "0"} },
            { Graphics::Setting::SetAttribute_DOUBLEBUFFER   , {"OpenGL",  "SetAttribute_DOUBLEBUFFER", "1"} },
            { Graphics::Setting::SetAttribute_STENCIL_SIZE   , {"OpenGL",  "SetAttribute_STENCIL_SIZE", "0"} },
            { Graphics::Setting::ClearColor   , {"OpenGL",  "ClearColor", "0.008,0.435,0.729"} },
        };

        return defSettings;
    }

}