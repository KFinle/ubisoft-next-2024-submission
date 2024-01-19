#pragma once
#include "Physics.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"

//////////////////////////////////////////////////////////////////////////
// Transform, Physics, and Input should definitely be decoupled, but    //
// for a small game with only one instance of a Player entity I think	//
// going for simplicity over robustness is worthwhile for dev experience//	
//																		//
// Addtionally, with the scope of the game limited as it is, I think a  //
// more OOP-esque component setup is serviceable for the task at hand.	//	
//////////////////////////////////////////////////////////////////////////
class Player : public Component<Player>
{
public:
	Player() : Component(Updatable | Renderable) {}
	Physics physics;
	Transform transform;
	Mesh mesh;
	void Update(float delta_time);
	void Render();
	bool using_x = false;
	bool using_y = false;

	// we'll use these to customize pivoting if needed
	float last_x = 0;
	float last_y = 0;
};
