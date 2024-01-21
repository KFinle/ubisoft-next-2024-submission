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

	Load();
}

GameplayScene::~GameplayScene()
{
	OnDestroy();
}

void GameplayScene::OnLoad()
{
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

	if (App::IsKeyPressed(VK_RETURN))
	{
		this->Load();
	}


	player->GetComponent<Player>()->Update(delta_time);
	raycaster->rays = raycaster->CalculateRays(*player, level);

	hidemap = App::IsKeyPressed(VK_TAB) ? true : false;

	raycaster->num_rays = hidemap ? WINDOW_WIDTH : 15;
	raycaster->fov_degrees = hidemap ? 60 : 10;


	for (auto* proj : player->GetComponent<Player>()->active_projectiles)
	{
		auto collision_lambda = [&](float x, float y)
		{
			return player->GetComponent<Player>()->collider.CheckWallCollision(x, y, *level);
		};
		proj->SetCollisionCallback(collision_lambda);
		
	}

}



void GameplayScene::OnDestroy()
{
	//player->~Entity();
	//delete player;
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
