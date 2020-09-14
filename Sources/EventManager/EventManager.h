#pragma once

#include "IEventObserver.h"
#include "IEvent.h"

#define LIB_API __declspec(dllexport)

namespace EventManager
{
    LIB_API void ProcessEvents();
    LIB_API void PushObserver(IEventObserver* observer, EventType evType);
    LIB_API void PopObserver(IEventObserver* observer, EventType evType);
    LIB_API void PushEvent(EventType evType, const std::string& sender);
}
