#include "Camera.h"
#include "SDL_opengl.h"

namespace Graphics
{

    Camera::Camera()
    {

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
        frameWidth_ = (float)frameWidth;
        frameHeight_ = (float)frameHeight;
    }

    float Camera::WindowCoordToWorldX(float x) const
    {
        return x - frameWidth_ * 0.5f;
    }

    float Camera::WindowCoordToWorldY(float y) const
    {
        return y - frameHeight_ * 0.5f;
    }

    float Camera::WorldCoordToWindowX(float x) const
    {
        return x + frameWidth_ * 0.5f;
    }

    float Camera::WorldCoordToWindowY(float y) const
    {
        return y + frameHeight_ * 0.5f;
    }

}