#pragma once
#include "../math/Mathf.h"
#include "../math/MathUtility.h"
#include "../Globals.h"
#include "Component.h"
#include "functional"
#include "../levels/Level.h"

struct Projectile : public Component<Projectile>
{
	enum projectile_type
	{
		basic, bomb, light
	};
	
	Projectile() : Component(CollidingComponent | RenderableComponent)
	{
		m_id = TypeIDGenerator<Projectile>::GenerateNewID<Projectile>();
	}

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
				col = Vector3(1, 0, 1);
				delta_x = -delta_x;
			}

			// check vertical collision
			if (collision_callback && collision_callback(curr_x, MathUtility::ScaleToVirtualHeight(new_y)))
			{
				col = Vector3(1, .5, 0.7);
				delta_y = -delta_y;
			}

			transform.position.SetX(transform.position.GetX() + delta_x * physics.current_speed * delta_time);
			transform.position.SetY(transform.position.GetY() + delta_y * physics.current_speed * delta_time);
			lifetime -= delta_time;

		}
	}

	void Render()
	{
		if (active) ShapeRenderer::RenderShapeWithNSides
		(
			MathUtility::ScaleToVirtualWidth(transform.position.GetX()),
			MathUtility::ScaleToVirtualHeight(transform.position.GetY()),
			size,
			//0.635, 1, 0.024,
			col.GetX(), col.GetY(), col.GetZ(),
			36
		);
	}

	void Launch(const Transform &launch_point)
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

	Vector3 col = Vector3(0.635, 1, 0.024);
	Transform transform;
	Physics physics;
	bool launched = false;
	float launch_speed = 1;
	projectile_type type = basic;
	bool hit = false;
	float size = 15;
	float delta_y;
	float delta_x;
	float next_x;
	float next_y;
	bool active = false;


	const Level* level = nullptr;

	float lifetime = 3;
	ComponentTypeID m_id;
	std::function<bool(float, float)> collision_callback;
};
