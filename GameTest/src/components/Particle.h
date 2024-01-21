#pragma once 


struct Particle : public Component<Particle>
{
	enum particle_emitter
	{
		bomb, wall, goal, death
	};
	Particle(){}

	particle_emitter emmiter_type;
	Transform transform;
	Physics physics;

};