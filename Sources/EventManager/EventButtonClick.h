#pragma once

#include "IEvent.h"

namespace EventManager
{
    class EventButtonClick : public IEvent
    {
    public:
        EventButtonClick(const std::string& sender);
        const IEventParams* GetParams() const override { return nullptr; }
    };
}