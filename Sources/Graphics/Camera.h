#pragma once

namespace Graphics
{
    class Camera
    {
    public:
        Camera();
        void set2D(float centerX, float centerY, int frameWidth, int frameHeight);
        float WindowCoordToWorldX(float x) const;
        float WindowCoordToWorldY(float y) const;
        float WorldCoordToWindowX(float x) const;
        float WorldCoordToWindowY(float y) const;
    private:
        float centerX_;
        float centerY_;
        float frameWidth_;
        float frameHeight_;
    };
}