#pragma once

#include <string>

namespace EventManager
{
    enum class EventType;
    struct IEventParams
    {
    };

    class IEvent
    {
    public:
        explicit IEvent(EventType type, bool isSystem): type_(type),  isSystem_(isSystem) {};
        virtual ~IEvent() {};
        EventType GetType() const { return type_; }
        virtual const IEventParams* GetParams() const = 0;
    private:
        EventType type_;
        bool isSystem_;
    };

}