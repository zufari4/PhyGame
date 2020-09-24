#pragma once


#include "SystemEvent.h"

namespace EventManager
{
    struct EventWindowResize : SystemEvent
    {
        EventWindowResize() : SystemEvent(EventType::WindowResize) {}
        int width = 0;
        int height = 0;
    };
}