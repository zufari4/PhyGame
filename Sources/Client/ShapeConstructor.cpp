#include "ShapeConstructor.h"
#include "Graphics.h"

void ShapeConstructor::AddPoint(float x, float y)
{
    points_.push_back({ x,y });
}

void ShapeConstructor::Draw()
{
    DrawShape();
    DrawPoints();

}

void ShapeConstructor::DrawPoints()
{
    for (const auto& p : points_) {
        Graphics::DrawPoint(p.x, p.y);
    }
}

void ShapeConstructor::DrawShape()
{

}
