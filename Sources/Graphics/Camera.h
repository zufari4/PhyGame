#pragma once

#include "IEventObserver.h"

namespace Graphics
{
    class Camera: public EventManager::IEventObserver
    {
    public:
        Camera();
        void set2D(float centerX, float centerY, int frameWidth, int frameHeight);
        float WindowCoordToWorldX(int x) const;
        float WindowCoordToWorldY(int y) const;
        int WorldCoordToWindowX(float x) const;
        int WorldCoordToWindowY(float y) const;
        void EventHandling(const EventManager::BaseEvent& event) override;
    private:
        float centerX_;
        float centerY_;
        int frameWidth_;
        int frameHeight_;
        bool  is2D_;
    };
}