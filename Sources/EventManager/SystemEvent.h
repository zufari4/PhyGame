#pragma once

#include "BaseEvent.h"

typedef union SDL_Event SDL_Event;

namespace EventManager
{
    struct SystemEvent : BaseEvent
    {
        explicit SystemEvent(EventType type) : BaseEvent(type, true), sysEvent (nullptr) {}
        virtual ~SystemEvent() {};
        const SDL_Event* sysEvent;
    };
}