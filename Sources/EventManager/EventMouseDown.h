#pragma once

#include "BaseEvent.h"

namespace EventManager
{
    struct EventMouseDown: BaseEvent
    {
        EventMouseDown() : BaseEvent(EventType::MouseDown) {}
        int x = 0;
        int y = 0;
        int button = 0;
    };
}