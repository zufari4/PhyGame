#pragma once

namespace EventManager
{
    enum class EventType;

    class IEvent
    {
    public:
        virtual ~IEvent() {};
        virtual EventType GetType() const = 0;
    };
}