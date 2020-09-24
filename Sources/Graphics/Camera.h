#pragma once

#include "IEventObserver.h"

namespace Graphics
{
    class Camera: public EventManager::IEventObserver
    {
    public:
        Camera();
        void set2D(float centerX, float centerY, int frameWidth, int frameHeight);
        float WindowCoordToWorldX(float x) const;
        float WindowCoordToWorldY(float y) const;
        float WorldCoordToWindowX(float x) const;
        float WorldCoordToWindowY(float y) const;
        void EventHandling(const EventManager::BaseEvent& event) override;
    private:
        float centerX_;
        float centerY_;
        float frameWidth_;
        float frameHeight_;
        bool  is2D_;
    };
}