#pragma once
#include "IEventObserver.h"
#include "IEvent.h"
#include "SettingsManager.h"
#include <atomic>
#include <string>

class Client: public EventManager::IEventObserver
{
public:
    Client();
    bool Init();
    void Run();
    void Free();
    void EventHandling(const EventManager::IEvent& event) override;
private:
    static std::string GetConfigFileName();
    static std::string GetDataDir();

    std::atomic_bool workFlag_;
    SettingsManager settingsManager_;
};