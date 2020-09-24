#pragma once

#include "SystemEvent.h"

namespace EventManager
{
    struct EventKeyDown : SystemEvent
    {
        EventKeyDown() : SystemEvent(EventType::KeyDown) {}
        unsigned key = 0;
    };
}