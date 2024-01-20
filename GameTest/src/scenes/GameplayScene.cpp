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
		raycaster->RenderRays();
	if (hidemap)
	{
		raycaster->Render3D();
	}
		
	if (!hidemap)
	{
		level->BuildMap();
		player->GetComponent<Player>()->Render();
	}

	if (player->GetComponent<Player>()->collider.currently_colliding)
	{
		player->GetComponent<Player>()->collider.DrawColliderLines();
	}



}

// for updating systems
void GameplayScene::Update(float delta_time)
{
	player->GetComponent<Player>()->Update(delta_time);
	raycaster->rays = raycaster->CalculateRays(*player, level);

	hidemap = App::IsKeyPressed(VK_TAB) ? true : false;

	HandleCollisions<Collider>();
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
