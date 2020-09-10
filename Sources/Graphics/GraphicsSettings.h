#pragma once

#include "SettingsManager.h"

namespace Graphics
{
    enum Setting : int
    {
        WindowTitleText,
        WindowWidth,
        WindowHeight,
        WindowIsFullscreen,
        WindowVSyncEnable,
        HintRenderScaleQuality,
        SetAttribute_DOUBLEBUFFER,
        SetAttribute_DEPTH_SIZE,
        SetAttribute_STENCIL_SIZE,
        SetAttribute_CONTEXT_MAJOR_VERSION,
        SetAttribute_CONTEXT_MINOR_VERSION,
        SetAttribute_ACCELERATED_VISUAL,
        Enable_GL_BLEND,
        Enable_GL_TEXTURE_2D,
        Enable_GL_LINE_SMOOTH,
        Enable_GL_DEPTH_TEST,
        Enable_GL_CULL_FACE,
        Enable_GL_MULTISAMPLE,
        Enable_GL_POLYGON_SMOOTH,
        Hint_GL_POINT_SMOOTH_HINT,
        Hint_GL_LINE_SMOOTH_HINT,
        BlendFunc_GL_SRC_ALPHA,
        ClearColor
    };
    const SettingsManager::tdProperties& GetDefaultSettings();
}