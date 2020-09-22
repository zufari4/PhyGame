#pragma once

#include "IEvent.h"

namespace EventManager
{
    class EventQuit : public IEvent
    {
    public:
        EventQuit();
        const IEventParams* GetParams() const override { return nullptr; }
    };
}