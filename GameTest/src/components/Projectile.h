#pragma once
#include "../math/Mathf.h"
#include "../math/MathUtility.h"
#include "../Globals.h"
#include "Component.h"

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
			transform.position.SetX(transform.position.GetX() + delta_x * physics.current_speed * delta_time);
			transform.position.SetY(transform.position.GetY() + delta_y * physics.current_speed * delta_time);
			lifetime -= delta_time;

		}
	}

	void Render()
	{
		if (active) ShapeRenderer::RenderShapeWithNPolygons
		(
			MathUtility::ScaleToVirtualWidth(transform.position.GetX()),
			MathUtility::ScaleToVirtualHeight(transform.position.GetY()),
			size,
			0.635, 1, 0.024,
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

	Transform transform;
	Physics physics;
	Collider collider;
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

	int mp;

	float lifetime = 3;
	ComponentTypeID m_id;
};
