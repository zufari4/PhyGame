#include "ShapeConstructor.h"
#include "Graphics.h"
#include "EventManager.h"
#include "EventType.h"
#include "EventMouseDown.h"
#include "EventMouseUp.h"
#include "EventMouseMove.h"

ShapeConstructor::ShapeConstructor()
    : pointSize_(16.0f)
    , pointColorNormal_ { 0.5f, 0.5f, 0.5f, 0.5f }
    , pointColorHover_ { 0.5f, 0.5f, 0.5f, 1.0f }
    , pointColorSelected_ { 0.3f, 0.3f, 0.3f, 1.0f }
    , lineColor_ { 0.5f, 0.5f, 0.5f, 0.5f }
    , hoverPoint_(-1)
{
    EventManager::PushObserver(this, EventManager::EventType::MouseDown);
    EventManager::PushObserver(this, EventManager::EventType::MouseUp);
    EventManager::PushObserver(this, EventManager::EventType::MouseMove);
}

ShapeConstructor::~ShapeConstructor()
{
    EventManager::PopObserver(this, EventManager::EventType::MouseDown);
    EventManager::PopObserver(this, EventManager::EventType::MouseUp);
    EventManager::PopObserver(this, EventManager::EventType::MouseMove);
}

void ShapeConstructor::AddPoint(float x, float y)
{
    std::lock_guard<std::mutex> g(pointsMutex_);
    points_.push_back({ x,y });
}

void ShapeConstructor::Draw()
{
    std::lock_guard<std::mutex> g(pointsMutex_);
    DrawShape();
    DrawPoints();

}

void ShapeConstructor::DrawPoints()
{
     if (!points_.empty()) Graphics::DrawPoints(points_, pointSize_, pointColorNormal_);
     if (hoverPoint_ != -1) {
         Graphics::DrawPoint(points_[hoverPoint_], pointSize_, pointColorHover_);
     }
}

void ShapeConstructor::DrawShape()
{
    if (points_.size() > 1) Graphics::DrawLines(points_, lineColor_);
}

void ShapeConstructor::EventHandling(const EventManager::IEvent& event)
{
    switch (event.GetType())
    {
    case EventManager::EventType::MouseDown: {

    } break;
    case EventManager::EventType::MouseUp: {
        const EventManager::MouseUpParams* params = (const EventManager::MouseUpParams*)event.GetParams();
        if (params->button == 1) {
            AddPoint((float)params->x, (float)params->y);
        }
    } break;
    case EventManager::EventType::MouseMove: {
        const EventManager::MouseMoveParams* params = (const EventManager::MouseMoveParams*)event.GetParams();
        std::lock_guard<std::mutex> g(pointsMutex_);
        hoverPoint_ = -1;
        for (size_t i = 0; i < points_.size(); ++i) {
            if (CursorInPoint((float)params->x, (float)params->y, points_[i])) {
                hoverPoint_ = i;
                break;
            }
        }
    } break;
    }
}

bool ShapeConstructor::CursorInPoint(float cursorX, float cursorY, const Point& point) const
{
    const float dx = point.x - cursorX;
    const float dy = point.y - cursorY;
    const float r  = pointSize_ * 0.5f;
    const float lengthSquared = dx * dx + dy * dy;
    return lengthSquared < r * r;
}
