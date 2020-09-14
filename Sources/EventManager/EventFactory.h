#pragma once

#include "IEvent.h"
#include "EventType.h"
#include <memory>

typedef union SDL_Event;

namespace EventManager
{
    std::unique_ptr<IEvent> CreateEvent(const SDL_Event& srcEvent);
    EventType GetEventType(const SDL_Event& srcEvent);
    std::unique_ptr<IEvent> CreateEvent(EventType type, const std::string& sender);
}