#include "EventMouseDown.h"
#include "EventType.h"

namespace EventManager
{
    EventMouseDown::EventMouseDown()
        : IEvent(EventType::MouseDown, true)
    {

    }

    const IEventParams* EventMouseDown::GetParams() const
    {
        return &mouseParams_;
    }

    void EventMouseDown::SetX(int val)
    {
        mouseParams_.x = val;
    }

    void EventMouseDown::SetY(int val)
    {
        mouseParams_.y = val;
    }

    void EventMouseDown::SetButton(int val)
    {
        mouseParams_.button = val;
    }
}