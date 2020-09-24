#pragma once


#include "BaseEvent.h"

namespace EventManager
{
    struct EventWindowResize : BaseEvent
    {
        EventWindowResize() : BaseEvent(EventType::WindowResize) {}
        int width = 0;
        int height = 0;
    };
}