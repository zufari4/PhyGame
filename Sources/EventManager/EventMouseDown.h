#pragma once

#include "SystemEvent.h"

namespace EventManager
{
    struct EventMouseDown: SystemEvent
    {
        EventMouseDown() : SystemEvent(EventType::MouseDown) {}
        int x = 0;
        int y = 0;
        int button = 0;
    };
}