#pragma once

namespace Graphics
{
    class Camera
    {
    public:
        Camera();
        void set2D(float centerX, float centerY, int frameWidth, int frameHeight);
    };
}