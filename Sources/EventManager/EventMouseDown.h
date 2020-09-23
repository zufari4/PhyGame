#pragma once

#include "IEvent.h"

namespace EventManager
{
    struct MouseDownParams : IEventParams
    {
        int x = 0;
        int y = 0;
        int button = 0;
    };

    class EventMouseDown : public IEvent
    {
    public:
        EventMouseDown();
        const IEventParams* GetParams() const override;
        void SetX(int val);
        void SetY(int val);
        void SetButton(int val);
    private:
        MouseDownParams mouseParams_;
    };
}