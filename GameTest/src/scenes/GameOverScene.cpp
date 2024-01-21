#include "stdafx.h"
#include "GameOverScene.h"
#include "../App/app.h"
GameOverScene::GameOverScene()
{
	this->m_scene_type = scene_type::gameover;

	Load();
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Render()
{
	App::Print(_WINDOW_WIDTH / 2, _WINDOW_HEIGHT / 2, "UR DEAD LOL");
	App::Print(_WINDOW_WIDTH / 2, _WINDOW_HEIGHT - 100, "PRESS [ENTER]");

}

void GameOverScene::Update(float deltaTime)
{
}

void GameOverScene::OnLoad()
{
	Scene::OnLoad();
}

void GameOverScene::OnDestroy()
{
	Scene::OnDestroy();
}

void GameOverScene::Load()
{
	Scene::Load();
}

void GameOverScene::Destroy()
{
	Scene::Destroy();
}
