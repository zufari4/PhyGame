#pragma once

#include "IEvent.h"

namespace EventManager
{
    class EventQuit : public IEvent
    {
    public:
        EventType GetType() const override;
    };
}