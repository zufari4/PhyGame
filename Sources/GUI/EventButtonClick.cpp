#include "EventButtonClick.h"
#include "EventType.h"

namespace EventManager
{

    EventButtonClick::EventButtonClick():
        IEvent(EventType::ButtonClick, false)
    {

    }

    void EventButtonClick::SetFileActive(const std::string& val)
    {
        params.fileActive = val;
    }

    void EventButtonClick::SetSender(const std::string& val)
    {
        params.sender = val;
    }

}