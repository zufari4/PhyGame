#pragma once

#include "BaseEvent.h"

namespace EventManager
{
    struct EventMouseMove : BaseEvent
    {
        EventMouseMove() : BaseEvent(EventType::MouseMove) {}
        int x = 0;
        int y = 0;
    };
}