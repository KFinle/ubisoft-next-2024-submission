#pragma once
//////////////////////////////////////////////////////////////////////////////////////////////
// There's no way I'm going to use all of this, but I figure it's better to have			//
// it and not use it than it is to have to whip them up on the spot on a per-case basis		//
// during the prompt weekend.																//
//																							//
// I know I could just make use of the <cmath> library, but I'd prefer to know I'm working  //
// with floats every time.																	//
//////////////////////////////////////////////////////////////////////////////////////////////
// I am also aware there is some redundacy on the some functions here, most notably in the  //
// trigonomic functions. This file was created in the ~dark times~ when I was unaware of    //
// sinf, cosf, etc... whoops.																//
//////////////////////////////////////////////////////////////////////////////////////////////


class Mathf
{
public:

	// static constants
	static const float Epsilon;
	static const float EpsilonNormalSqrt;
	//static const float PI;										// declared in AppSettings.h
	static const float Infinity;
	static const float NegativeInfinity;
	static const float Deg2Rad;
	static const float Rad2Deg;

	// utility functions
	static float Sin(float f);
	static float Cos(float f);
	static float Tan(float f);
	static float Asin(float f);
	static float Acos(float f);
	static float Atan(float f);
	static float Atan2(float y, float x);
	static float Sqrt(float f);
	static float Abs(float f);
	static int Abs(int value);
	static float Min(float a, float b);
	static int Min(int a, int b);
	static float Max(float a, float b);
	static int Max(int a, int b);
	static float Pow(float f, float p);
	static float Exp(float power);
	static float Log(float f);
	static float Log10(float f);
	static float Ceil(float f);
	static float Floor(float f);
	static float Round(float f);
	static int CeilToInt(float f);
	static int FloorToInt(float f);
	static int RoundToInt(float f);
	static float Sign(float f);
	static float Clamp(float value, float min, float max);
	static int Clamp(int value, int min, int max);
	static float ClampFloat(float value);
	static float Lerp(float a, float b, float t);
	static float LerpUnclamped(float a, float b, float t);
	static float LerpAngle(float a, float b, float t);
	static float MoveTowards(float current, float target, float max_delta);
	static float MoveTowardsAngle(float current, float target, float max_delta);
	static float SmoothStep(float from, float to, float t);
	static bool Approximately(float a, float b);
	static float Repeat(float t, float length);
	static float PingPong(float t, float length);
	static float InverseLerp(float a, float b, float value);
	static float DeltaAngle(float current, float target);
};