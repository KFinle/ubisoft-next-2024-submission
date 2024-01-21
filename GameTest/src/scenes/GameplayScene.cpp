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
	level = new Level();
	level->level_map = level->RandomizeLevel();
	level->BuildMap();
	player->GetComponent<Player>()->current_level = level;
	player->GetComponent<Player>()->active_projectiles.clear();
	player->GetComponent<Player>()->bullets_on_screen = 0;
	player->GetComponent<Player>()->active_bomb = nullptr;
	player->GetComponent<Player>()->bombs_remaining = player->GetComponent<Player>()->max_bombs;
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
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 400, std::string(" -------- ").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 420, std::string("- Cleared -").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 440, std::string("- ").append(std::to_string(levels_cleared)).append(" - ").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 460, std::string(" -------- ").c_str());

}

// for updating systems
void GameplayScene::Update(float delta_time)
{
	CheckLevelState(delta_time);

	// for testing level generation
	if (App::IsKeyPressed(VK_RETURN))
	{
		this->Load();
	}


	player->GetComponent<Player>()->Update(delta_time);
	raycaster->rays = raycaster->CalculateRays(*player, level);

	// 3d view
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
	delete raycaster;
}

void GameplayScene::Load()
{

	OnLoad();
}

void GameplayScene::Destroy()
{
	OnDestroy();
}

void GameplayScene::CheckLevelState(float delta_time)
{
	if (player->GetComponent<Player>()->destroyed_goal)
	{
		TransitionToGameOver(delta_time);
	}
	if (player->GetComponent<Player>()->destroyed_death)
	{
		TransitionToGameOver(delta_time);
	}


	if (level->breakable_found) level->level_map.at(level->breakable_found) = Cell::EMPTY;
	if (level->death_found) this->scene_ended = true;
	if (level->goal_found)
	{
		levels_cleared++;
		this->Load();
	}
		
}

void GameplayScene::TransitionToGameOver(float delta_time)
{
	transition_time -= delta_time;
	if (transition_time < 0)
	{
		this->scene_ended = true;
	}
}
