#pragma once

#include <string>

namespace EventManager
{
    enum class EventType;

    class IEvent
    {
    public:
        explicit IEvent(const std::string& sender) : sender_(sender) {};
        virtual ~IEvent() {};
        virtual EventType GetType() const = 0;
        const std::string& GetSender() const { return sender_; } 
    private:
        std::string sender_;
    };

}