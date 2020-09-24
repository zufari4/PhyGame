#pragma once

namespace EventManager
{
    enum class EventType
    {
        Undefined,
        Quit,
        MouseMove,
        MouseDown,
        MouseUp,
        MouseWheel,
        WindowResize,
        TextInput,
        KeyDown,
        KeyUp,
        ButtonClick,
    };
}