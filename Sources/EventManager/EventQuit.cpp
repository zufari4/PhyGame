#include "EventQuit.h"
#include "EventType.h"

namespace EventManager
{
    EventType EventQuit::GetType() const
    {
        return EventType::Quit;
    }
}