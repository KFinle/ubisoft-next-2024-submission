#include "stdafx.h"
#include "ShapeRenderer.h"
#include "../App/app.h"

void ShapeRenderer::RenderSquare(float sx, float sy, float ex, float ey, float r, float b, float g)
{
	App::DrawLine(sx, sy, sx, ey, r, g, b);
	App::DrawLine(sx, ey, ex, ey, r, g, b);
	App::DrawLine(ex, ey, ex, sy, r, g, b);
	App::DrawLine(ex, sy, sx, sy, r, g, b);
	App::DrawLine(ex, ey, sx, sy, r, g, b);
}


void ShapeRenderer::RenderShapeWithNSides(float cx, float cy, float radius, float r, float g, float b, int numSegments, float rotation)
{
    for (int i = 0; i < numSegments; ++i)
    {
        float theta1 = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float theta2 = 2.0f * PI * static_cast<float>(i + 1) / static_cast<float>(numSegments);

        float x1 = cx + radius * std::cos(theta1 + rotation);
        float y1 = cy + radius * std::sin(theta1 + rotation);
        float x2 = cx + radius * std::cos(theta2 + rotation);
        float y2 = cy + radius * std::sin(theta2 + rotation);

        App::DrawLine(x1, y1, x2, y2, r, g, b);
    }
}

