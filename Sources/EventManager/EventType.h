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
        WindowResize,
        ButtonClick
    };
}