#pragma once

#include "IEvent.h"

namespace EventManager
{
    class EventQuit : public IEvent
    {
    public:
        EventQuit();
        EventType GetType() const override;
    };
}