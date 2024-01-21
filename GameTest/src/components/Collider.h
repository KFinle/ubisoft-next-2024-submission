#pragma once
#include "Component.h"
#include "../math/Vector3.h"
#include "../levels/Level.h"


struct Collider : public Component<Collider> 
{
	Collider() {}
	Vector3 GetPosition();
	void DrawColliderLines();
	bool CheckCollision(const Collider& other) const;
	static Cell CheckWallCollision(int direction_x, int direction_y, Level& level);
	void InitializeCollider(Vector3 position, float width, float height)
	{
		this->position = position;
		this->width = width;
		this->height = height;
	}
	void Update(float delta_time)
	{
		// look for other colliders 
	}
	float width = 10;
	float height = 10;
	Vector3 position;

	bool currently_colliding = false;

};