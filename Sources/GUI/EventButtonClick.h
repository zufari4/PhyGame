#pragma once

#include "IEvent.h"

namespace EventManager
{
    struct ButtonClickParam: IEventParams
    {
        std::string sender;
        std::string fileActive;
    };
    class EventButtonClick : public IEvent
    {
    public:
        EventButtonClick();
        const IEventParams* GetParams() const override { return &params; }
        void SetFileActive(const std::string& val);
        void SetSender(const std::string& val);
    private:
        ButtonClickParam params;
    };
}