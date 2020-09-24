#pragma once

#include "SystemEvent.h"

namespace EventManager
{
    struct EventQuit : SystemEvent
    {
        EventQuit() : SystemEvent(EventType::Quit) {}
    };
}