#include "EventButtonClick.h"
#include "EventType.h"

namespace EventManager
{

    EventButtonClick::EventButtonClick(const std::string& sender):
        IEvent(EventType::ButtonClick, sender, false)
    {

    }

}