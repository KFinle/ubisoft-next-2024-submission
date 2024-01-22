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

// Renders the scene
void GameOverScene::Render()
{
	App::Print(WINDOW_WIDTH / 3.5f, WINDOW_HEIGHT / 2, std::string("GAME OVER").c_str(), 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24);
	App::Print(WINDOW_WIDTH / 3.5f, WINDOW_HEIGHT / 2 - 50, std::string("[Press [ENTER] to continue...").c_str(), 1, 1, 1, GLUT_BITMAP_HELVETICA_18);
	App::Print(50, 200, std::string("Tip: bombs can blow up your goal!  ").c_str());
	App::Print(50, 150, std::string("Tip: shooting red things is bad!").c_str());
}

void GameOverScene::Update(float deltaTime){}

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
