#pragma once

#include "IEvent.h"
#include "EventType.h"
#include <memory>

union SDL_Event;

namespace EventManager
{
    const IEvent& GetSystemEvent(const SDL_Event& srcEvent);
    EventType GetEventType(const SDL_Event& srcEvent);
    std::unique_ptr<IEvent> CreateEvent(EventType type, const std::string& sender);
}