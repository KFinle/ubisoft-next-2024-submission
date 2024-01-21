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
	raycaster = new Raycaster();


}


void GameplayScene::Render()
{
	//if (hidemap)
	//{
	//	raycaster->Render3D();
	//}
	//	
	//if (!hidemap)
	//{
		level->BuildMap();
		raycaster->RenderRays();
		player->GetComponent<Player>()->Render();
	//}

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

	for (auto* proj : player->GetComponent<Player>()->active_projectiles)
	{
		if (proj->mp > 0)
		{
			if (level->level_map.at(proj->mp) != 0)
			{
				level->level_map.at(proj->mp) == 0;
			}
		}
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
