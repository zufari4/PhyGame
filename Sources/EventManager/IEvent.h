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
        explicit IEvent(EventType type, const std::string& sender, bool isSystem): type_(type),  sender_(sender), isSystem_(isSystem) {};
        virtual ~IEvent() {};
        const std::string& GetSender() const { return sender_; } 
        EventType GetType() const { return type_; }
        virtual const IEventParams* GetParams() const = 0;
    private:
        EventType type_;
        std::string sender_;
        bool isSystem_;
    };

}