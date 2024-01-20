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
	Vector3 spawn = Level::GetPositionFromLevelCell(level->player_spawn);
	player = std::make_shared<Entity<Player>>(spawn);
	player->GetComponent<Player>()->current_level = level;

	raycaster = new Raycaster();

}


void GameplayScene::Render()
{
	POINT mousePos;
	float x, y;
	GetCursorPos(&mousePos);	// Get the mouse cursor 2D x,y position			
	ScreenToClient(MAIN_WINDOW_HANDLE, &mousePos);
	x = (float)mousePos.x;
	y = (float)mousePos.y;
	x = (x * (2.0f / WINDOW_WIDTH) - 1.0f);
	y = -(y * (2.0f / WINDOW_HEIGHT) - 1.0f);

#if APP_USE_VIRTUAL_RES		
	APP_NATIVE_TO_VIRTUAL_COORDS(x, y);
#endif
	Vector3 mouse = Vector3(x, y, 0);
	//App::Print(500, 500, mouse.ToString().c_str());
	App::Print(500, 500, std::to_string(player->GetComponent<Player>()->transform.direction_angle).c_str());
	raycaster->Render3D();
	raycaster->RenderRays();
	player->GetComponent<Player>()->Render();
	level->BuildMap();


}

// for updating systems
void GameplayScene::Update(float delta_time)
{
	player->GetComponent<Player>()->Update(delta_time);
	raycaster->rays = raycaster->CalculateRays(*player, level);
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
