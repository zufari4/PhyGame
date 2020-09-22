#include "EventWindowResize.h"
#include "EventType.h"

namespace EventManager
{
    EventWindowResize::EventWindowResize()
        : IEvent(EventType::WindowResize, "", true)
    {

    }

    void EventWindowResize::SetWindowHeight(int val)
    {
        winParams_.height = val;
    }

    void EventWindowResize::SetWindowWidth(int val)
    {
        winParams_.width = val;
    }

    const IEventParams* EventWindowResize::GetParams() const
    {
        return &winParams_;
    }
}