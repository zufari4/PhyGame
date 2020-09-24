#pragma once

#include "SystemEvent.h"

namespace EventManager
{
    struct EventKeyUp : SystemEvent
    {
        EventKeyUp() : SystemEvent(EventType::KeyUp) {}
        unsigned key = 0;
    };
}