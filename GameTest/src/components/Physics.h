#pragma once
#include "../math/Vector3.h"
struct Physics
{
	Vector3 velocity;
	float current_speed;
	float turn_speed;
	float acceleration;
	float deceleration;
	float max_speed;
	float gravity;
	float turnaround_factor;
};
