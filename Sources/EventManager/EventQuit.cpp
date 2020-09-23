#include "EventQuit.h"
#include "EventType.h"

namespace EventManager
{

    EventQuit::EventQuit():
        IEvent(EventType::Quit, true)
    {

    }
}