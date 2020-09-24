#pragma once

#include "EventTypes.h"
#include <string>

namespace EventManager
{
    struct BaseEvent
    {
        explicit BaseEvent(EventType _type, bool _isSystemEvent = false) : type(_type), isSystemEvent(_isSystemEvent) {}
        virtual ~BaseEvent() {}
        EventType type;
        bool isSystemEvent;
    };
}