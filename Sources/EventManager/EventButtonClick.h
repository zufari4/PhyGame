#pragma once

#include "IEvent.h"

namespace EventManager
{
    class EventButtonClick : public IEvent
    {
    public:
        EventButtonClick(const std::string& sender);
        EventType GetType() const override;
    };
}