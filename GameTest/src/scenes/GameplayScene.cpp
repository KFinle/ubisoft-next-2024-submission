#include "stdafx.h"
#include "GameplayScene.h"
//#include "../entities/Entity.h"
//#include "../components/Component.h"
#include "../App/app.h"
#include "../App/main.h"
#include "string"

// Constructor
GameplayScene::GameplayScene()
{
	this->m_scene_type = scene_type::gameplay;
	Load();
}

// Destructor
GameplayScene::~GameplayScene()
{
	OnDestroy();
}

// Initialize gameplay scene 
void GameplayScene::OnLoad()
{
	level = new Level();
	level->level_map = level->RandomizeLevel();
	level->BuildMap();
	raycaster = new Raycaster();

	player->GetComponent<Player>()->InitializePlayer();
	player->GetComponent<Player>()->current_level = level;
	player->GetComponent<Player>()->transform.SetPosition(level->GetPositionFromLevelCell(level->player_spawn));
}

// Draw the scene
void GameplayScene::Render()
{
	// 3D raycast view
	if (hidemap)
	{
		raycaster->Render3D();
		level->DrawMapSmall();
	}
		
	// Regular gameplay
	if (!hidemap)
	{
		level->BuildMap();
		raycaster->RenderRays();
		player->GetComponent<Player>()->Render();
	}

	// Level information (should be decoupled if I have time)
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 400, std::string(" -------- ").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 420, std::string("- Cleared -").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 440, std::string("- ").append(std::to_string(levels_cleared)).append(" - ").c_str());
	App::Print(WINDOW_WIDTH - MAP_CELL_SIZE * 2, MAP_HEIGHT * MAP_CELL_SIZE - MAP_CELL_SIZE / 2 - 460, std::string(" -------- ").c_str());
}

// called every frame 
void GameplayScene::Update(float delta_time)
{
	// Have walls been broken?
	CheckLevelState(delta_time);

	// Restart Gameplay
	// Used for testing level generation
	if (App::IsKeyPressed(VK_RETURN))
	{
		levels_cleared = 0;
		this->Load();
	}

	// update the Player
	player->GetComponent<Player>()->Update(delta_time);

	// Calculate rays 
	raycaster->rays = raycaster->CalculateRays(*player, level);

	// 3d view
	hidemap = App::IsKeyPressed(VK_TAB) ? true : false;

	// raycaster properties
	raycaster->num_rays = hidemap ? WINDOW_WIDTH : 30;
	raycaster->fov_degrees = hidemap ? 60 : 25;


	// Check if player projectiles have collided with walls 
	for (auto* proj : player->GetComponent<Player>()->active_projectiles)
	{
		auto collision_lambda = [&](float x, float y)
		{
			// I know this is bad practice but it's very late and I'm very tired
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


// clean up scene
void GameplayScene::OnDestroy()
{
	delete player;
	delete level;
	delete raycaster;
}

// Load the scene
void GameplayScene::Load()
{
	OnLoad();
}

// Destroy the scene
void GameplayScene::Destroy()
{
	OnDestroy();
}

// Checks the game state | Gameover processed here 
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

// Small transition period before GameOver scene
void GameplayScene::TransitionToGameOver(float delta_time)
{
	transition_time -= delta_time;
	if (transition_time < 0)
	{
		this->scene_ended = true;
	}
}
