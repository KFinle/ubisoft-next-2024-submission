#include "stdafx.h"
#include "MathUtility.h"
#include "Vector3.h"
#include "../App/app.h"
#include "../App/main.h"


static const float& Max(const float& a, const float& b)
{
	return (a < b) ? b : a;
}

float MathUtility::DegreeToRadians(float degrees)
{
	return degrees * PI / 180.0f;
}

float MathUtility::RadiansToDegrees(float radians)
{
	return radians * 180.0f / PI;
}

float MathUtility::NormalizedValue(float value, float min, float max)
{
	return (value - min) / (max - min);
}

float MathUtility::ModRadians(float radians)
{
	if (radians < 0) return radians + 2 * PI;
	if (radians > 2 * PI) return radians - 2 * PI;
	return radians;
}

float MathUtility::ModDegrees(float angle)
{
	if (angle > 359) angle -= 360;
	if (angle < 0) angle += 360;
	return angle;
}

float MathUtility::ScaleToNativeHeight(float num)
{
	return ((num / WINDOW_HEIGHT * 2.0f) - 1);
}

float MathUtility::ScaleToNativeWidth(float num)
{
	return ((num / WINDOW_WIDTH * 2.0f) - 1);
}

float MathUtility::ScaleToVirtualHeight(float num)
{
	return ((num + 1.0f) * WINDOW_HEIGHT) / 2.0f;
}

float MathUtility::ScaleToVirtualWidth(float num)
{
	return ((num + 1.0f) * WINDOW_WIDTH) / 2.0f;

}
