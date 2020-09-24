#pragma once
#include "IEventObserver.h"
#include "BaseEvent.h"
#include "SettingsManager.h"
#include "GameState.h"
#include "ShapeConstructor.h"
#include <atomic>
#include <string>
#include <memory>

class Client: public EventManager::IEventObserver
{
public:
    Client();
    bool Init();
    void Run();
    void Free();
    void EventHandling(const EventManager::BaseEvent& event) override;
private:
    static std::string GetConfigFileName();
    static std::string GetDataDir();

    std::atomic_bool workFlag_;
    std::unique_ptr<SettingsManager> settingsManager_;
    GameState state_;
    std::unique_ptr<ShapeConstructor> shapeConstructor_;
};