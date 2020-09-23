#include "EventMouseMove.h"
#include "EventType.h"

namespace EventManager
{
    EventMouseMove::EventMouseMove()
        : IEvent(EventType::MouseMove, true)
    {

    }

    const IEventParams* EventMouseMove::GetParams() const
    {
        return &mouseParams_;
    }

    void EventMouseMove::SetX(int val)
    {
        mouseParams_.x = val;
    }

    void EventMouseMove::SetY(int val)
    {
        mouseParams_.y = val;
    }
}