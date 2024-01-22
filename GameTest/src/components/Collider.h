#pragma once
#include "Component.h"
#include "../math/Vector3.h"
#include "../levels/Level.h"

/**
* Collider Component
* 
* To be attached to Entity objects requiring collision.
*/
struct Collider : public Component<Collider> 
{
	// Methods
	Collider() {}
	Vector3 GetPosition() const;
	void DrawColliderLines() const;
	bool CheckCollision(const Collider& other) const;
	void InitializeCollider(Vector3 position, float width, float height)
	{
		this->position = position;
		this->width = width;
		this->height = height;
	}
	void Update(float delta_time);

	// static methods
	static Cell CheckWallCollision(int direction_x, int direction_y, Level& level);

	// Included components
	Vector3 position;

	// Data members
	float width = 10;
	float height = 10;
	bool currently_colliding = false;


};