#pragma once 
#include "../math/Mathf.h"

// Particle types
enum particle_emitter
{
	bomb_emitter, wall_emitter, goal_emitter, death_emitter, breakable_emitter
};

// Particle Component
// Can be added to any Entity or other Components
// Intended use-case is to store a Pool of particles 
// on any Entity or Component that needs to display particle VFX
struct Particle : public Component<Particle>
{
	Particle(){}

	// Sets the initial position and type of particle
	void Set(Transform transform, particle_emitter type)
	{
		this->transform = transform;
		switch (type)
		{
		case particle_emitter::bomb_emitter:
			m_colour.Set(1, 0, 0);
			size = 4;
			num_sides = 10;
			dispersion_rate = 1.0f;
			break;
		case particle_emitter::breakable_emitter:
			m_colour.Set(1, 0, 1);
			size = 5;
			num_sides = 4;
			dispersion_rate = 1.0f;
			break;
		case particle_emitter::wall_emitter:
			m_colour.Set(1, 1, 1);
			size = 5;
			num_sides = 4;
			dispersion_rate = 3.0f;
			break;
		case particle_emitter::goal_emitter:
			m_colour.Set(0, 1, 0);
			size = 15;
			num_sides = 4;
			dispersion_rate = 6.5f;
			break;
		case particle_emitter::death_emitter:
			m_colour.Set(1, 0, 0);
			size = 15;
			num_sides = 9;
			dispersion_rate = 6.5f;
			break;
		default:
			m_colour.Set(1, 0, 0);
			size = 4;
			num_sides = 10;
			dispersion_rate = 1;
			break;
		}
	}

	// Called every frame
	void Update(float delta_time)
	{
		CalculateDeltas(MathUtility::RandomFloat(0, 359));
		transform.position.SetX(transform.position.GetX() + (dispersion_rate * delta_x) * delta_time);
		transform.position.SetY(transform.position.GetY() + (dispersion_rate * delta_y) * delta_time);
	}

	// Display the particle
	void Render()
	{
		ShapeRenderer::RenderShapeWithNSides
		(
			MathUtility::ScaleToVirtualWidth(transform.position.GetX()),
			MathUtility::ScaleToVirtualHeight(transform.position.GetY()),
			size, m_colour.r, m_colour.g, m_colour.b, num_sides
		);
	}

	// Calculate trajectory
	void CalculateDeltas(float direction)
	{
		delta_x = Mathf::Cos(MathUtility::DegreeToRadians(direction));
		delta_y = Mathf::Sin(MathUtility::DegreeToRadians(direction));
	}

	// included components
	particle_emitter emmiter_type;
	Transform transform;
	render_colour m_colour;

	// data members 
	float size = 4;
	float delta_x;
	float delta_y;
	float lifetime = 1.5f;
	float dispersion_rate = 1.0f;
	int num_sides = 10;

};