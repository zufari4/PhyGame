#include "EventMouseUp.h"
#include "EventType.h"

namespace EventManager
{
    EventMouseUp::EventMouseUp()
        : IEvent(EventType::MouseUp, "", true)
    {

    }

    const IEventParams* EventMouseUp::GetParams() const
    {
        return &mouseParams_;
    }

    void EventMouseUp::SetX(int val)
    {
        mouseParams_.x = val;
    }

    void EventMouseUp::SetY(int val)
    {
        mouseParams_.y = val;
    }

    void EventMouseUp::SetButton(int val)
    {
        mouseParams_.button = val;
    }

}