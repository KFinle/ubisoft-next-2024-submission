#include "stdafx.h"
#include "Player.h"
#include "../../App/app.h"
#include "../math/Mathf.h"
#include "../rendering/ShapeRenderer.h"
#include "../math/MathUtility.h"
#include "../Globals.h"


// Called every frame
void Player::Update(float delta_time)
{

	// Projectile cleanup
	for (int i = 0; i < active_projectiles.size(); i++)
	{
		if (dynamic_cast<Bomb*>(active_projectiles[i]))
		{
			if (bomb_active && static_cast<Bomb*>(active_projectiles[i])->lifetime <= 0)
			{
				if (active_bomb->goal_destroyed) destroyed_goal  = true;
				if (active_bomb->death_hit)
				{
					destroyed_death = true;
				}
				bullets_on_screen--;
				bombs->ReturnPoolObject(active_bomb);
				active_bomb = nullptr;
				active_projectiles.erase(active_projectiles.begin() + i);
			}
		}
		else if (active_projectiles[i]->lifetime < 0)
		{
			bullets_on_screen--;
			bullets->ReturnPoolObject(active_projectiles[i]);
			active_projectiles.erase(active_projectiles.begin() + i);
		}
	}


	// deceleration 
	if (!App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_UP) &&
		!App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_DOWN))
	{
		using_y = false;
		physics.velocity.SetY(Mathf::Lerp(physics.velocity.GetY(), 0, physics.deceleration * delta_time));
	}
	if (!App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_LEFT) &&
		!App::IsKeyPressed(APP_PAD_EMUL_LEFT_THUMB_RIGHT))
	{
		using_x = false;
		physics.velocity.SetX(Mathf::Lerp(physics.velocity.GetX(), 0, physics.deceleration * delta_time));
	}

	// weapon selection
	if (App::IsKeyPressed(0x31)) selected_weapon = basic;
	if (App::IsKeyPressed(0x32)) selected_weapon = bomb;

	// Shooting
	if (App::IsKeyPressed(VK_SPACE))
	{

		// Get Bomb from pool
		if (selected_weapon == projectile_type::basic && refire_timer <= 0)
		{
			bullets_on_screen++;
			Bullet* new_projectile = bullets->GetPoolObject();
			active_projectiles.push_back(new_projectile);
			new_projectile->Launch(transform);
			refire_timer = max_refire_timer;
		}

		// get Bullet from pool
		if (selected_weapon == projectile_type::bomb && !active_bomb && bombs_remaining > 0)
		{
			bullets_on_screen++;
			bomb_active = true;
			Bomb* new_bomb = bombs->GetPoolObject();
			new_bomb->SetLevelCallback([&]() -> Level* {return current_level; });
			active_bomb = new_bomb;
			active_bomb->type = projectile_type::bomb;
			active_projectiles.push_back(new_bomb);
			new_bomb->Launch(transform);
			bombs_remaining--;
		}
	}

	// detonate bomb
	if (App::IsKeyPressed(VK_SHIFT))
	{
		if (bomb_active && active_bomb != nullptr)
		{
			if (!active_bomb->bursting)
			{
				active_bomb->bursting = true;
			}
		}
	}

	// set current speed 
	if (using_y)
	{
		physics.current_speed += physics.acceleration;
		if (physics.current_speed > physics.max_speed) physics.current_speed >= physics.max_speed;
	}

	// clockwise rotation
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		transform.direction_angle -= physics.turn_speed * delta_time;
	}
	// counterclockwise rotation
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		transform.direction_angle += physics.turn_speed * delta_time;
	}
	// up
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		using_y = true;
		if (last_y != 1) physics.current_speed = physics.current_speed / physics.turnaround_factor;
		physics.velocity.SetY(physics.velocity.GetY() + physics.current_speed * delta_time);
		last_y = 1;
	}
	//down
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		using_y = true;
		if (last_y != -1) physics.current_speed = physics.current_speed / physics.turnaround_factor;
		physics.velocity.SetY(physics.velocity.GetY() - physics.current_speed * delta_time);
		last_y = -1;
	}

	// clamp velocity
	if (physics.velocity.GetX() > physics.max_speed)  physics.velocity.SetX(physics.max_speed);
	if (physics.velocity.GetY() > physics.max_speed)  physics.velocity.SetY(physics.max_speed);
	if (physics.velocity.GetX() < -physics.max_speed) physics.velocity.SetX(-physics.max_speed);
	if (physics.velocity.GetY() < -physics.max_speed) physics.velocity.SetY(-physics.max_speed);

	// Apply velocity
	transform.position.SetY(transform.position.GetY() + physics.velocity.GetY()); 

	// Add real collision here if I have time 
	if (MathUtility::ScaleToVirtualHeight(transform.position.GetY()) < MAP_CELL_SIZE + 20)
	{
		transform.position.SetY(MathUtility::ScaleToNativeHeight(MAP_CELL_SIZE + 20));
	}
	if (MathUtility::ScaleToVirtualHeight(transform.position.GetY()) > WINDOW_HEIGHT - MAP_CELL_SIZE - 20)
	{
		transform.position.SetY(MathUtility::ScaleToNativeHeight(WINDOW_HEIGHT - MAP_CELL_SIZE - 20 ));
	}

	// update any active projectiles
	for (auto& projectile : active_projectiles)
	{
		if (dynamic_cast<Bomb*>(projectile))
		{
			static_cast<Bomb*>(projectile)->Update(delta_time);
		}
		else projectile->Update(delta_time);
	}
	refire_timer -= delta_time;
}


// Display the player
void Player::Render()
{
	// Render Projectiles
	for (auto& projectile : active_projectiles)
	{
		if (dynamic_cast<Bomb*>(projectile))
		{
			static_cast<Bomb*>(projectile)->Render();
		}
		else projectile->Render();
	}

	// turret extend-o-matic body  
	ShapeRenderer::RenderSquare
	(
		MathUtility::ScaleToVirtualWidth(transform.position.GetX() - 0.005), MAP_CELL_SIZE, 
		MathUtility::ScaleToVirtualWidth(transform.position.GetX() + 0.005), 
		MathUtility::ScaleToVirtualHeight(transform.position.GetY()), 
		1, 0, 0.89
	);
	// turret base
	ShapeRenderer::RenderSquare
	(
		MathUtility::ScaleToVirtualWidth(transform.position.GetX() - 0.05), MAP_CELL_SIZE,
		MathUtility::ScaleToVirtualWidth(transform.position.GetX() + 0.05), MAP_CELL_SIZE + 10,
		1, 0, 0.8
	);

	// head
	ShapeRenderer::RenderShapeWithNSides
	(
		MathUtility::ScaleToVirtualWidth(transform.position.GetX()), 
		MathUtility::ScaleToVirtualHeight(transform.position.GetY()), 
		30, 1, 0, 1, 4, 
		MathUtility::DegreeToRadians(MathUtility::ModDegrees(transform.direction_angle + 5))
	);

	// inner head
	ShapeRenderer::RenderShapeWithNSides(MathUtility::ScaleToVirtualWidth
	(
		transform.position.GetX()), 
		MathUtility::ScaleToVirtualHeight(transform.position.GetY()), 
		10, 1, 1, 1, 7, 
		MathUtility::DegreeToRadians(MathUtility::ModDegrees(transform.direction_angle))
	);


	// Display current gameplay information | Decoupling into UI rendering if I have time
	std::string weapon_text = selected_weapon == bomb ? "Bombs" : "Bullets";
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2, std::string(" -------- ").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 20, std::string("- Bombs -").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 40, std::string(" --- ").append(std::to_string(bombs_remaining)).append(" --- ").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 60, std::string(" -------- ").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 200, std::string(" -------- ").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 220, std::string("- Weapon-").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 240, std::string(" - ").append(weapon_text).append(" - ").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 260, std::string(" -------- ").c_str());

}

// Initial player values 
void Player::InitializePlayer()
{
	active_projectiles.clear();
	bullets_on_screen = 0;
	active_bomb = nullptr;
	bombs_remaining = max_bombs;
	physics.max_speed = 0.01;
	physics.turn_speed = 50;
}



