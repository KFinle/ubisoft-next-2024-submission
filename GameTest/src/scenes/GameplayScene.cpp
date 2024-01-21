#include "stdafx.h"
#include "GameplayScene.h"
//#include "../entities/Entity.h"
//#include "../components/Component.h"
#include "../App/app.h"
#include "../App/main.h"
#include "string"
GameplayScene::GameplayScene()
{
	this->m_scene_type = scene_type::gameplay;
	levels_cleared = 0;
	Load();
}

GameplayScene::~GameplayScene()
{
	OnDestroy();
}

void GameplayScene::OnLoad()
{
	if (player->GetComponent<Player>()->active_projectiles.size() > 0)
	{
		player->GetComponent<Player>()->active_projectiles.clear();
		player->GetComponent<Player>()->bullets_on_screen = 0;
	}
	level = new Level();
	level->level_map = level->RandomizeLevel();
	level->BuildMap();
	player->GetComponent<Player>()->current_level = level;
	player->GetComponent<Player>()->transform.SetPosition(level->GetPositionFromLevelCell(level->player_spawn));
	raycaster = new Raycaster();
}


void GameplayScene::Render()
{
	if (hidemap)
	{
		raycaster->Render3D();
		level->DrawMapSmall();
	}
		
	if (!hidemap)
	{
		level->BuildMap();
		raycaster->RenderRays();
		player->GetComponent<Player>()->Render();
	}

	//if (player->GetComponent<Player>()->collider.currently_colliding)
	//{
	//	player->GetComponent<Player>()->collider.DrawColliderLines();
	//}



}

// for updating systems
void GameplayScene::Update(float delta_time)
{
	CheckLevelState();

	// for testing level generation
	if (App::IsKeyPressed(VK_RETURN))
	{
		this->Load();
	}


	player->GetComponent<Player>()->Update(delta_time);
	raycaster->rays = raycaster->CalculateRays(*player, level);

	hidemap = App::IsKeyPressed(VK_TAB) ? true : false;

	raycaster->num_rays = hidemap ? WINDOW_WIDTH : 30;
	raycaster->fov_degrees = hidemap ? 60 : 25;


	for (auto* proj : player->GetComponent<Player>()->active_projectiles)
	{
		auto collision_lambda = [&](float x, float y)
		{
			// I know this is bad but it's very late and I'm very tired
			// To be cleaned up if I have time
			return player->GetComponent<Player>()->collider.CheckWallCollision(x, y, *level) == Cell::WALL	 ? true : 
				   player->GetComponent<Player>()->collider.CheckWallCollision(x, y, *level) == Cell::BREAKABLE ? true :
				   player->GetComponent<Player>()->collider.CheckWallCollision(x, y, *level) == Cell::BORDER ? true :
				   false;
		};
		if (dynamic_cast<Bomb*>(proj)) static_cast<Bomb*>(proj)->SetCollisionCallback(collision_lambda);
		else proj->SetCollisionCallback(collision_lambda);
	}

}

void GameplayScene::OnDestroy()
{
	delete player;
	delete level;
}

void GameplayScene::Load()
{

	OnLoad();
}

void GameplayScene::Destroy()
{
	OnDestroy();
}

void GameplayScene::CheckLevelState()
{
	if (level->breakable_found) level->level_map.at(level->breakable_found) = Cell::EMPTY;
	if (level->death_found) this->scene_ended = true;
	if (level->goal_found)
	{
		levels_cleared++;
		this->Load();
	}
		
}
