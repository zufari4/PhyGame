#include "Camera.h"
#include "EventManager.h"
#include "SDL_opengl.h"
#include "Graphics.h"

namespace Graphics
{

    Camera::Camera()
    {
        EventManager::PushObserver(this, EventManager::EventType::WindowResize);
    }

    void Camera::set2D(float centerX, float centerY, int frameWidth, int frameHeight)
    {
        glViewport(0, 0, (GLsizei)frameWidth, (GLsizei)frameHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(
            centerX - frameWidth / 2.0, 
            centerX + frameWidth / 2.0, 
            centerY + frameHeight / 2.0, 
            centerY - frameHeight / 2.0, 
            0, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        centerX_ = centerX;
        centerY_ = centerY;
        frameWidth_ = frameWidth;
        frameHeight_ = frameHeight;
        is2D_ = true;
    }

    float Camera::WindowCoordToWorldX(int x) const
    {
        return (float)x - (float)frameWidth_ * 0.5f;
    }

    float Camera::WindowCoordToWorldY(int y) const
    {
        return (float)y - (float)frameHeight_ * 0.5f;
    }

    int Camera::WorldCoordToWindowX(float x) const
    {
        return (int)(x + frameWidth_ * 0.5f);
    }

    int Camera::WorldCoordToWindowY(float y) const
    {
        return (int)(y + frameHeight_ * 0.5f);
    }

    void Camera::EventHandling(const EventManager::BaseEvent& event)
    {
        switch (event.type)
        {
        case EventManager::EventType::WindowResize:
            if (is2D_) {
                set2D(centerX_, centerY_, Graphics::GetFrameWidth(), Graphics::GetFrameHeight());
            }
            break;
        }
    }

}