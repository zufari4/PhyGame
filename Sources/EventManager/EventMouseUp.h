#pragma once

#include "BaseEvent.h"

namespace EventManager
{
    struct EventMouseUp : BaseEvent
    {
        EventMouseUp() : BaseEvent(EventType::MouseUp) {}
        int x = 0;
        int y = 0;
        int button = 0;
    };
}