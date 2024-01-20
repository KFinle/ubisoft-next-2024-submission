#pragma once
#include "../math/Vector3.h"
struct Physics
{
	Vector3 velocity = Vector3(Vector3::Zero());
	float current_speed = 0;
	float turn_speed = 2;
	float acceleration = 5;
	float deceleration = 5;
	float max_speed = 2;
	float gravity;
	float turnaround_factor = 3;
};
