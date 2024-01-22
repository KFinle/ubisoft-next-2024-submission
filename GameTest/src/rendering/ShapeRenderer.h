#pragma once
#include "RenderColour.h"

// This is just a wrapper for some repeated App::DrawLine() calls I was making 
class ShapeRenderer
{
public:
	static void RenderSquare(float sx, float sy, float ex, float ey, float r = 1, float b = 1, float g = 1);
	static void RenderShapeWithNSides(float cx, float cy, float radius, float r, float g, float b, int numSegments, float radians = MathUtility::DegreeToRadians(45));
};

