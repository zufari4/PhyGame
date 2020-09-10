#pragma once

#include "IEvent.h"

namespace EventManager
{
    class IEventObserver
    {
    public:
        virtual ~IEventObserver() {};
        virtual void EventHandling(const IEvent& event) = 0;
    };
}