#include "EventButtonClick.h"
#include "EventType.h"

namespace EventManager
{

    EventButtonClick::EventButtonClick(const std::string& sender):
        IEvent(sender)
    {

    }

    EventManager::EventType EventButtonClick::GetType() const
    {
        return EventType::ButtonClick;
    }

}