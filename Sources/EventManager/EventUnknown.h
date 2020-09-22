#pragma once

#include "IEvent.h"

namespace EventManager
{
    class EventUnknow: public IEvent
    {
    public:
        EventUnknow();
        const IEventParams* GetParams() const override { return nullptr; }
    };
}