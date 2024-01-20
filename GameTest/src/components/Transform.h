#pragma once
#include "../math/Vector3.h"
struct Transform : public BaseComponent
{
	Vector3 position = Vector3(Vector3::Zero());
	Vector3 scale = Vector3(Vector3::Zero());
	//Vector3 rotation = Vector3(Vector3::Right());
	float direction_angle = 0;
	void SetPosition(Vector3 to_position)
	{
		position = to_position;
	}
};
