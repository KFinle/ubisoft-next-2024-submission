#pragma once
#include "Vector3.h"
#include <cmath>
#include <random>

//////////////////////////////////////////////////////////////////////////
// Several utility math functions that warranted a different class than	//
// those included in Mathf.h		 									//
//////////////////////////////////////////////////////////////////////////
class MathUtility
{
public:
	static float DegreeToRadians(float degrees);
	static float RadiansToDegrees(float radians);
	static float NormalizedValue(float value, float min, float max);
	static float ModRadians(float radians);
	static float ModDegrees(float degrees);
	static float ScaleToNativeHeight(float num);
	static float ScaleToNativeWidth(float num);
	static float ScaleToVirtualHeight(float num);
	static float ScaleToVirtualWidth(float num);
	static Vector3 GetCell(Vector3 position);
	static float RandomFloat(float min, float max);

};
