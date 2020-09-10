#pragma once

#include "IEvent.h"
#include <memory>

typedef union SDL_Event;

namespace EventManager
{
    enum class EventType
    {
        Undefined,
        Quit,
        MouseMove,
        MouseDown,
        MouseUp,
        WindowResize
    };

    class EventQuit : public IEvent
    {
    public:
        EventType GetType() const override;
    };
    std::unique_ptr<IEvent> CreateEvent(const SDL_Event& srcEvent);
    EventType GetEventType(const SDL_Event& srcEvent);
}