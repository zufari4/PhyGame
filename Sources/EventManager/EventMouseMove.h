#pragma once

#include "SystemEvent.h"

namespace EventManager
{
    struct EventMouseMove : SystemEvent
    {
        EventMouseMove() : SystemEvent(EventType::MouseMove) {}
        int x = 0;
        int y = 0;
    };
}