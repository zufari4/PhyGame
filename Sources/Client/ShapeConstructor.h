#pragma once

#include "Point.h"
#include <vector>

class ShapeConstructor
{
public:
    void AddPoint(float x, float y);
    void Draw();
private:
    void DrawPoints();
    void DrawShape();
    std::vector<Point> points_;
};