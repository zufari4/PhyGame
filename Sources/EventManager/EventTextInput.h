#pragma once

#include "SystemEvent.h"

namespace EventManager
{
    struct EventTextInput : SystemEvent
    {
        EventTextInput() : SystemEvent(EventType::TextInput) {}
        std::string text;
    };
}