#pragma once


#include "IEvent.h"

namespace EventManager
{
    struct WindowResizeParams: IEventParams
    {
        int width = 0;
        int height = 0;
    };

    class EventWindowResize : public IEvent
    {
    public:
        EventWindowResize();
        void SetWindowWidth(int val);
        void SetWindowHeight(int val);
        const IEventParams* GetParams() const override;
    private:
        WindowResizeParams winParams_;
    };
}