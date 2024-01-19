#include "stdafx.h"
#include "GameplayScene.h"
//#include "../entities/Entity.h"
//#include "../components/Component.h"
#include "../App/app.h"

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
	level = std::make_shared<Level>();
	level->level_map = level->RandomizeLevel();
	level->BuildMap();
}


void GameplayScene::Render()
{
	level->BuildMap();

	App::Print(200, 100, "GameplayScene");

}

// for updating systems
void GameplayScene::Update(float delta_time)
{
	//player->GetComponent<Player>()->Update(delta_time);
}



void GameplayScene::OnDestroy()
{
	//player->~Entity();
	//delete player;
}

void GameplayScene::Load()
{

	OnLoad();
}

void GameplayScene::Destroy()
{
	OnDestroy();
}
