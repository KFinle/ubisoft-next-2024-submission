#pragma once
#include "../math/Vector3.h"
#include "Component.h"
struct Physics : public Component<Physics>
{
	void Update(float delta_time) {}
	Vector3 velocity = Vector3(Vector3::Zero());
	float current_speed = 0;
	float turn_speed = 2;
	float acceleration = .1;
	float deceleration = 5;
	float max_speed = 2;
	float gravity;
	float turnaround_factor = 3;
};
