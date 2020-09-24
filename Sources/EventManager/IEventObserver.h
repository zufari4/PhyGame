#pragma once

#include "BaseEvent.h"

namespace EventManager
{
    class IEventObserver
    {
    public:
        virtual ~IEventObserver() {};
        virtual void EventHandling(const BaseEvent& event) = 0;
    };
}