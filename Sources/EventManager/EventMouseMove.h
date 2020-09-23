#pragma once

#include "IEvent.h"

namespace EventManager
{
    struct MouseMoveParams : IEventParams
    {
        int x = 0;
        int y = 0;
    };

    class EventMouseMove : public IEvent
    {
    public:
        EventMouseMove();
        const IEventParams* GetParams() const override;
        void SetX(int val);
        void SetY(int val);
    private:
        MouseMoveParams mouseParams_;
    };
}