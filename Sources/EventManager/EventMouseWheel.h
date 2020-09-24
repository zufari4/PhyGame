#pragma once

#include "SystemEvent.h"

namespace EventManager
{
    struct EventMouseWheel : SystemEvent
    {
        EventMouseWheel() : SystemEvent(EventType::MouseWheel) {}
        int delta = 0;
    };
}