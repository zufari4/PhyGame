#include "EventQuit.h"
#include "EventType.h"

namespace EventManager
{

    EventQuit::EventQuit():
        IEvent("SYSTEM")
    {

    }

    EventType EventQuit::GetType() const
    {
        return EventType::Quit;
    }
}