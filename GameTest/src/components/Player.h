#pragma once
#include "Physics.h"
#include "Component.h"
#include "Transform.h"
#include "Collider.h"
#include "Bomb.h"
#include "Bullet.h"
#include "../levels/Level.h"
#include "../pools/Pool.h"
#include "unordered_map"

//////////////////////////////////////////////////////////////////////////
// Transform, Physics, and Input should definitely be decoupled, but    //
// for a small game with only one instance of a Player entity I think	//
// going for simplicity over robustness is worthwhile for dev experience//	
//																		//
// Addtionally, with the scope of the game limited as it is, I think a  //
// more OOP-esque component setup is serviceable for the task at hand.	//	
//////////////////////////////////////////////////////////////////////////

// Player Component
// Used to make any Entity into a Player. 
// Can be initialized as a standalone object if needed
class Player : public Component<Player>
{
public:
	Player()
	{ 
		InitializePlayer();
	}

	void Update(float delta_time);
	void Render();
	void InitializePlayer();

	// data members 
	bool using_x = false;
	bool using_y = false;
	bool bomb_active = false;
	float refire_timer = 0;
	float max_refire_timer = 0.1;
	float last_x = 0;
	float last_y = 0;
	std::string weapon_text = "";
	int bullets_on_screen = 0;
	int max_bombs = 5;
	int bombs_remaining = 5;
	bool destroyed_goal = false;
	bool destroyed_death = false;
	std::vector<Bullet*> active_projectiles;
	Bomb* active_bomb = nullptr;
	Level* current_level = nullptr;
	projectile_type selected_weapon = projectile_type::basic;

	// Includede components 
	Physics physics;
	Transform transform;
	Collider collider;
	Pool<Bullet>* bullets = Pool<Bullet>::GetInstance(1000);
	Pool<Bomb>* bombs = Pool<Bomb>::GetInstance(5);
};
