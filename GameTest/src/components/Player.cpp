#include "stdafx.h"
#include "Player.h"
#include "../../App/app.h"
#include "../math/Mathf.h"
#include "../rendering/ShapeRenderer.h"
#include "../math/MathUtility.h"
#include "../Globals.h"

void Player::Update(float delta_time)
{
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

	if (using_y)
	{
		physics.current_speed += physics.acceleration * delta_time;
		if (physics.current_speed > physics.max_speed) physics.current_speed >= physics.max_speed;
	}
	//if (!using_x && !using_y)
	//{
	//	physics.current_speed -= physics.acceleration * delta_time;
	//	if (physics.current_speed < 0) physics.current_speed = 0;
	//}

	//right
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		//using_x = true;
		//if (last_x != 1) physics.current_speed = physics.current_speed / physics.turnaround_factor;
		//physics.velocity.SetX(physics.velocity.GetX() + physics.current_speed);
		//last_x = 1;

		// rotation instead
		transform.direction_angle -= physics.turn_speed * delta_time;

	}
	// left
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		/*using_x = true;
		if (last_x != -1) physics.current_speed = physics.current_speed / physics.turnaround_factor;
		physics.velocity.SetX(physics.velocity.GetX() - physics.current_speed);
		last_x = -1;*/

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

	int next_x = (transform.position.GetX() + physics.velocity.GetX());
	int next_y = (transform.position.GetY() + physics.velocity.GetY());

	float temp_x = MathUtility::ScaleToVirtualWidth(transform.position.GetX()) + next_x;
	float temp_y = MathUtility::ScaleToVirtualHeight(transform.position.GetY()) + next_y;


	if (!collider.CheckWallCollision(temp_x, MathUtility::ScaleToVirtualHeight(transform.position.GetY()), *current_level))
	{
		transform.position.SetX(transform.position.GetX() + physics.velocity.GetX());
	}
	else transform.position.SetX(transform.position.GetX() - physics.velocity.GetX());
	if (!collider.CheckWallCollision(MathUtility::ScaleToVirtualWidth(transform.position.GetX()), temp_y, *current_level))
	{
		transform.position.SetY(transform.position.GetY() + physics.velocity.GetY());
	}
	else transform.position.SetY(transform.position.GetY() - physics.velocity.GetY());




	// prevent player moving out of bounds (likely not needed for this game, but it's nice to have safety)
	if (transform.position.GetX() < -1) transform.position.SetX(-1);
	if (transform.position.GetX() > 1) transform.position.SetX(1);
	if (transform.position.GetY() < -1) transform.position.SetY(-1);
	if (transform.position.GetY() > 1)	transform.position.SetY(1);
}

void Player::Render()
{

	//ShapeRenderer::RenderShapeWithNPolygons(MathUtility::ScaleToVirtualWidth(transform.position.GetX()), MathUtility::ScaleToVirtualHeight(transform.position.GetY()), 100, 1, 0, 1, 360, MathUtility::DegreeToRadians(MathUtility::ModDegrees(transform.direction_angle)));
	ShapeRenderer::RenderShapeWithNPolygons(MathUtility::ScaleToVirtualWidth(transform.position.GetX()), MathUtility::ScaleToVirtualHeight(transform.position.GetY()), 10, 1, 1, 1, 7, MathUtility::DegreeToRadians(MathUtility::ModDegrees(transform.direction_angle)));
	App::Print(111, 111, collider.position.ToString().c_str());
}

void Player::InitializePlayer()
{
	transform.position.Set(-0.8, 0, 0);
	physics.max_speed = 0.005;
	physics.turn_speed = 50;
	collider.InitializeCollider(transform.position, 100, 100);
}

