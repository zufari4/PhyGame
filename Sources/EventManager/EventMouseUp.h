#pragma once

#include "SystemEvent.h"

namespace EventManager
{
    struct EventMouseUp : SystemEvent
    {
        EventMouseUp() : SystemEvent(EventType::MouseUp) {}
        int x = 0;
        int y = 0;
        int button = 0;
    };
}