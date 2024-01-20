#include "stdafx.h"
#include "Player.h"
#include "../../App/app.h"
#include "../math/Mathf.h"
#include "../rendering/ShapeRenderer.h"
#include "../math/MathUtility.h"

void Player::Update(float delta_time)
{

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
		transform.direction_angle -= physics.turn_speed;

	}
	// left
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		/*using_x = true;
		if (last_x != -1) physics.current_speed = physics.current_speed / physics.turnaround_factor;
		physics.velocity.SetX(physics.velocity.GetX() - physics.current_speed);
		last_x = -1;*/

		// rotation instead
		transform.direction_angle += physics.turn_speed;



	}
	// up
	if (App::GetController().GetLeftThumbStickY() > 0.5f)
	{
		using_y = true;
		if (last_y != 1) physics.current_speed = physics.current_speed / physics.turnaround_factor;
		physics.velocity.SetY(physics.velocity.GetY() + physics.current_speed);
		last_y = 1;
	}
	//down
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		using_y = true;
		if (last_y != -1) physics.current_speed = physics.current_speed / physics.turnaround_factor;
		physics.velocity.SetY(physics.velocity.GetY() - physics.current_speed);
		last_y = -1;
	}


	// clamp velocity
	if (physics.velocity.GetX() > physics.max_speed)  physics.velocity.SetX(physics.max_speed);
	if (physics.velocity.GetY() > physics.max_speed)  physics.velocity.SetY(physics.max_speed);
	if (physics.velocity.GetX() < -physics.max_speed) physics.velocity.SetX(-physics.max_speed);
	if (physics.velocity.GetY() < -physics.max_speed) physics.velocity.SetY(-physics.max_speed);

	// apply velocity
	transform.position.SetX(transform.position.GetX() + physics.velocity.GetX() * delta_time);
	transform.position.SetY(transform.position.GetY() + physics.velocity.GetY() * delta_time);

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

}

