#include "stdafx.h"
#include "Player.h"
#include "../../App/app.h"
#include "../math/Mathf.h"
#include "../rendering/ShapeRenderer.h"
#include "../math/MathUtility.h"
#include "../Globals.h"

void Player::Update(float delta_time)
{
	for (int i = 0; i < active_projectiles.size(); i++)
	{
		if (active_projectiles[i]->lifetime < 0)
		{
			projectiles->ReturnPoolObject(active_projectiles[i]);
			active_projectiles.erase(active_projectiles.begin() + i);
		}
	}

	collider.position = transform.position;

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

	if (App::IsKeyPressed(VK_SPACE) && refire_timer <= 0)
	{
		Projectile* new_projectile = projectiles->GetPoolObject();
		active_projectiles.push_back(new_projectile);
		new_projectile->Launch(transform);
		refire_timer = max_refire_timer;
	}

	if (using_y)
	{
		physics.current_speed += physics.acceleration;
		if (physics.current_speed > physics.max_speed) physics.current_speed >= physics.max_speed;
	}

	//right
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		transform.direction_angle -= physics.turn_speed * delta_time;
	}
	// left
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		// rotation instead
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

	//int next_x = (transform.position.GetX() + physics.velocity.GetX());
	//int next_y = (transform.position.GetY() + physics.velocity.GetY());

	float temp_x = MathUtility::ScaleToVirtualWidth(transform.position.GetX()) + transform.position.GetX() + physics.velocity.GetX();
	float temp_y = MathUtility::ScaleToVirtualHeight(transform.position.GetY()) + transform.position.GetY() + physics.velocity.GetY();


	if (!collider.CheckWallCollision(temp_x, MathUtility::ScaleToVirtualHeight(transform.position.GetY()), *current_level))
	{
		transform.position.SetX(transform.position.GetX() + physics.velocity.GetX());
	}
	else transform.position.SetX(transform.position.GetX() - physics.velocity.GetX()*2);
	if (!collider.CheckWallCollision(MathUtility::ScaleToVirtualWidth(transform.position.GetX()), temp_y, *current_level))
	{
		transform.position.SetY(transform.position.GetY() + physics.velocity.GetY());
	}
	else transform.position.SetY(transform.position.GetY() - physics.velocity.GetY()*2);




	// prevent player moving out of bounds (likely not needed for this game, but it's nice to have safety)
	if (transform.position.GetX() < -1) transform.position.SetX(-1);
	if (transform.position.GetX() > 1) transform.position.SetX(1);
	if (transform.position.GetY() < -1) transform.position.SetY(-1);
	if (transform.position.GetY() > 1)	transform.position.SetY(1);


	//if (active_projectile != nullptr) active_projectile->Update(delta_time);
	for (auto& projectile : active_projectiles)
	{
		projectile->Update(delta_time);
	}

	refire_timer -= delta_time;
}

void Player::Render()
{
	//if (active_projectile != nullptr) active_projectile->Render();

	for (auto& projectile : active_projectiles)
	{
		projectile->Render();
	}

	ShapeRenderer::RenderSquare
	(
		MathUtility::ScaleToVirtualWidth(transform.position.GetX()), 0, 
		MathUtility::ScaleToVirtualWidth(transform.position.GetX()), 
		MathUtility::ScaleToVirtualHeight(transform.position.GetY()), 
		1, 0, 0.89
	);
	ShapeRenderer::RenderShapeWithNPolygons
	(
		MathUtility::ScaleToVirtualWidth(transform.position.GetX()), 
		MathUtility::ScaleToVirtualHeight(transform.position.GetY()), 
		30, 1, 0, 1, 3, 
		MathUtility::DegreeToRadians(MathUtility::ModDegrees(transform.direction_angle + 5))
	);
	ShapeRenderer::RenderShapeWithNPolygons(MathUtility::ScaleToVirtualWidth
	(
		transform.position.GetX()), 
		MathUtility::ScaleToVirtualHeight(transform.position.GetY()), 
		10, 1, 1, 1, 7, 
		MathUtility::DegreeToRadians(MathUtility::ModDegrees(transform.direction_angle))
	);
}

void Player::InitializePlayer()
{
	transform.position.Set(-0.8, 0, 0);
	physics.max_speed = 0.01;
	physics.turn_speed = 50;
	collider.InitializeCollider(transform.position, 100, 100);
	

}

