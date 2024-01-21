#pragma once 
#include "../math/Mathf.h"


struct Particle : public Component<Particle>
{
	enum particle_emitter
	{
		bomb, wall, goal, death
	};
	Particle()
	{
	}
	void Set(Transform transform)
	{
		this->transform = transform;
	}
	void Update(float delta_time)
	{
		CalculateDeltas(MathUtility::RandomFloat(0, 359));
		transform.position.SetX(transform.position.GetX() + delta_x * delta_time);
		transform.position.SetY(transform.position.GetY() + delta_y * delta_time);
	}
	void Render()
	{
		ShapeRenderer::RenderShapeWithNSides(
			MathUtility::ScaleToVirtualWidth(transform.position.GetX()), 
			MathUtility::ScaleToVirtualHeight(transform.position.GetY()), 
			4, 1, 0, 0, 10
		);
	}
	void CalculateDeltas(float direction)
	{
		delta_x = Mathf::Cos(MathUtility::DegreeToRadians(direction));
		delta_y = Mathf::Sin(MathUtility::DegreeToRadians(direction));
	}

	particle_emitter emmiter_type;
	Transform transform;
	float delta_x;
	float delta_y;
	float lifetime = 1.5f;
	float dispersion_rate = 0.5f;

};