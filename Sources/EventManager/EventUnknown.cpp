#include "EventUnknown.h"
#include "EventType.h"

namespace EventManager
{

    EventUnknow::EventUnknow()
        : IEvent(EventType::Undefined, "UNKNOWN", false)
    {

    }
}