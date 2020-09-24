#pragma once

#include "BaseEvent.h"

namespace EventManager
{
    struct EventButtonClick : BaseEvent
    {
        EventButtonClick() : BaseEvent(EventType::ButtonClick) {};
        std::string sender;
        std::string fileActive;
    };
}