#pragma once

#include "IEvent.h"

namespace EventManager
{
    struct MouseUpParams: IEventParams
    {
        int x = 0;
        int y = 0;
        int button = 0;
    };

    class EventMouseUp : public IEvent
    {
    public:
        EventMouseUp();
        const IEventParams* GetParams() const override;
        void SetX(int val);
        void SetY(int val);
        void SetButton(int val);
    private:
        MouseUpParams mouseParams_;
    };
}