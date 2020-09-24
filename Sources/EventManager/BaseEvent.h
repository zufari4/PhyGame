#pragma once

#include "EventTypes.h"
#include <string>

namespace EventManager
{
    struct BaseEvent
    {
        explicit BaseEvent(EventType _type) : type(_type) {}
        virtual ~BaseEvent() {}
        EventType type;
    };
}