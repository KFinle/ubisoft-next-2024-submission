#pragma once
#include "../math/Mathf.h"
#include "../math/MathUtility.h"
#include "../Globals.h"
#include "Component.h"
#include "functional"
#include "../levels/Level.h"
#include "Particle.h"
#include "../pools/Pool.h"

// Projectile type
enum projectile_type
{
	basic, bomb
};

/**
* Primary Projectile
* 
* Fast-moving bullet to serve at the primary ammunition for the player 
* Can be used as a componenet attached to an Entity in an EC system 
* or attached to an object as a data member if needed
*/
struct Bullet : public Component<Bullet>
{
	

	Bullet() : Component(CollidingComponent | RenderableComponent)
	{
		m_id = TypeIDGenerator<Bullet>::GenerateNewID<Bullet>();
	}

	// Called every frame 
	void Update(float delta_time) 
	{
		if (active)
		{
			// Update position based on speed and direction
			float new_x = transform.position.GetX() + delta_x * physics.current_speed * delta_time;
			float new_y = transform.position.GetY() + delta_y * physics.current_speed * delta_time;
			float curr_x = MathUtility::ScaleToVirtualWidth(transform.position.GetX());
			float curr_y = MathUtility::ScaleToVirtualHeight(transform.position.GetY());

			// check horizontal collision first
			if (collision_callback && collision_callback(MathUtility::ScaleToVirtualWidth(new_x), curr_y))
			{
				delta_x = -delta_x;
			}

			// check vertical collision
			if (collision_callback && collision_callback(curr_x, MathUtility::ScaleToVirtualHeight(new_y)))
			{
				delta_y = -delta_y;
			}

			// apply transformations
			transform.position.SetX(transform.position.GetX() + delta_x * physics.current_speed * delta_time);
			transform.position.SetY(transform.position.GetY() + delta_y * physics.current_speed * delta_time);
			lifetime -= delta_time;

		}
	}

	// Render the bullet
	void Render()
	{
		if (active) ShapeRenderer::RenderShapeWithNSides
		(
			MathUtility::ScaleToVirtualWidth(transform.position.GetX()),
			MathUtility::ScaleToVirtualHeight(transform.position.GetY()),
			size,
			col.GetX()*lifetime, col.GetY()*lifetime, col.GetZ(),
			15
		);
	}

	// Launch bullet
	void Launch(const Transform &launch_point)
	{
		launched = true;
		active = true;
		transform.SetPosition(launch_point.position);

		CalculateDeltas(launch_point.direction_angle);
		physics.current_speed = launch_speed;
	}

	// Calculate trajectory
	void CalculateDeltas(float direction)
	{
		delta_x = Mathf::Cos(MathUtility::DegreeToRadians(direction));
		delta_y = Mathf::Sin(MathUtility::DegreeToRadians(direction));
	}

	// For recieving information about its collisions
	void SetCollisionCallback(std::function<bool(float, float)> callback)
	{
		collision_callback = std::move(callback);
	}

	// other components (can be decoupled if time allows)
	projectile_type type = basic;
	Vector3 col = Vector3(1, .2, 1);
	Transform transform;
	Physics physics;
	Pool<Particle>* particles = Pool<Particle>::GetInstance(50);

	// Data members 
	bool launched = false;
	float launch_speed = 1;
	float size = 10;
	float delta_y;
	float delta_x;
	float next_x;
	float next_y;
	bool active = false;
	float lifetime = 3;
	ComponentTypeID m_id;

	// For recieving collision information
	std::function<bool(float, float)> collision_callback;
};
