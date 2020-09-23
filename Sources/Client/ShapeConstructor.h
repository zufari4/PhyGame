#pragma once

#include "Point.h"
#include "IEventObserver.h"
#include "Color4f.h"
#include <vector>
#include <mutex>

class ShapeConstructor : public EventManager::IEventObserver
{
public:
    ShapeConstructor();
    ~ShapeConstructor();
    void AddPoint(float x, float y);
    void Draw();
    void EventHandling(const EventManager::IEvent& event) override;
private:
    void DrawPoints();
    void DrawShape();
    bool CursorInPoint(float cursorX, float cursorY, const Point& point) const;

    std::vector<Point> points_;
    std::mutex pointsMutex_;
    float pointSize_;
    Graphics::Color4f pointColorNormal_;
    Graphics::Color4f pointColorHover_;
    Graphics::Color4f pointColorSelected_;
    Graphics::Color4f lineColor_;
    size_t hoverPoint_;
    size_t dragPoint_;
    float dragDeltaX_;
    float dragDeltaY_;
};
