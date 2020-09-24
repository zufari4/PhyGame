#pragma once

#include "BaseEvent.h"

namespace EventManager
{
    struct EventQuit : BaseEvent
    {
        EventQuit() : BaseEvent(EventType::Quit) {}
    };
}