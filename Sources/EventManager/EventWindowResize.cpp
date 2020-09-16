#include "EventWindowResize.h"
#include "EventType.h"

namespace EventManager
{
    EventWindowResize::EventWindowResize(int windowWidth, int windowHeight)
        : IEvent("SYSTEM")
        , windowWidth_(windowWidth)
        , windowHeight_(windowHeight)
    {

    }

    EventManager::EventType EventWindowResize::GetType() const
    {
        return EventType::WindowResize;
    }

    int EventWindowResize::GetWindowWidth() const
    {
        return windowWidth_;
    }

    int EventWindowResize::GetWindowHeight() const
    {
        return windowHeight_;
    }

}