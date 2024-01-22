#pragma once
#include "../math/Vector3.h"

// Transform Component
// Can be attached to any Entity requiring an in-world position
struct Transform : public Component<Transform>
{
	Vector3 position = Vector3(Vector3::Zero());
	Vector3 scale = Vector3(Vector3::Zero());
	float direction_angle = 0;
	void SetPosition(Vector3 to_position)
	{
		position = to_position;
	}
};
