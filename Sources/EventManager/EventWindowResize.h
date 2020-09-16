#pragma once


#include "IEvent.h"

namespace EventManager
{
    class EventWindowResize : public IEvent
    {
    public:
        EventWindowResize(int windowWidth, int windowHeight);
        EventType GetType() const override;
        int GetWindowWidth() const;
        int GetWindowHeight() const;
    private:
        int windowWidth_;
        int windowHeight_;
    };
}