#pragma once
#include "Particle.h"
#include "../pools/Pool.h"
#include "Bullet.h"

struct Bomb : public Bullet
{
	Bomb()
	{
		m_id = TypeIDGenerator<Bullet>::GenerateNewID<Bullet>();
	}

	void Update(float delta_time)
	{
		if (active)
		{
			Bullet::Update(delta_time);
		}
	}

	void Render()
	{
		if (active) ShapeRenderer::RenderShapeWithNSides
		(
			MathUtility::ScaleToVirtualWidth(transform.position.GetX()),
			MathUtility::ScaleToVirtualHeight(transform.position.GetY()),
			6,
			col.GetX() * lifetime, col.GetY() * lifetime, col.GetZ(),
			5
		);
	}

	void Launch(const Transform& launch_point)
	{
		launched = true;
		active = true;
		transform.SetPosition(launch_point.position);

		CalculateDeltas(launch_point.direction_angle);
		physics.current_speed = launch_speed;
	}

	void CalculateDeltas(float direction)
	{
		delta_x = Mathf::Cos(MathUtility::DegreeToRadians(direction));
		delta_y = Mathf::Sin(MathUtility::DegreeToRadians(direction));
	}
	void SetCollisionCallback(std::function<bool(float, float)> callback)
	{
		collision_callback = std::move(callback);
	}

	//Vector3 col = Vector3(0.635, 1, 0.024);
	Vector3 col = Vector3(1, 1, 1);

	Transform transform;
	Physics physics;
	bool launched = false;
	float launch_speed = 1;
	projectile_type type = basic;
	float size = 15;
	float delta_y;
	float delta_x;
	float next_x;
	float next_y;
	bool active = false;
	float lifetime = 3;
	ComponentTypeID m_id;
	std::function<bool(float, float)> collision_callback;

	// bomb stuff
	Pool<Particle>* particles = Pool<Particle>::GetInstance(50);
	bool bursting = false;
	bool exploded = false;
	float bomb_timer = 5;
};
