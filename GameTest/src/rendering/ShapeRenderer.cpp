#include "stdafx.h"
#include "ShapeRenderer.h"
#include "../App/app.h"
#include "../math/Mathf.h"

// Renders a square with a diagonal line in through the centre
void ShapeRenderer::RenderSquare(float sx, float sy, float ex, float ey, float r, float b, float g)
{
	App::DrawLine(sx, sy, sx, ey, r, g, b);
	App::DrawLine(sx, ey, ex, ey, r, g, b);
	App::DrawLine(ex, ey, ex, sy, r, g, b);
	App::DrawLine(ex, sy, sx, sy, r, g, b);
	App::DrawLine(ex, ey, sx, sy, r, g, b);
}

// Renders a regular polygon with any number of sides
void ShapeRenderer::RenderShapeWithNSides(float cx, float cy, float radius, float r, float g, float b, int numSegments, float rotation)
{
    for (int i = 0; i < numSegments; ++i)
    {
        float angle_1 = 2.0f * PI * static_cast<float>(i) / static_cast<float>(numSegments);
        float angle_2 = 2.0f * PI * static_cast<float>(i + 1) / static_cast<float>(numSegments);

        float x1 = cx + radius * Mathf::Cos(angle_1 + rotation);
        float y1 = cy + radius * Mathf::Sin(angle_1 + rotation);
        float x2 = cx + radius * Mathf::Cos(angle_2 + rotation);
        float y2 = cy + radius * Mathf::Sin(angle_2 + rotation);

        App::DrawLine(x1, y1, x2, y2, r, g, b);
    }
}

