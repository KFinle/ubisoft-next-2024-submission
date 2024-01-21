#include "stdafx.h"
#include "MenuScene.h"
#include "../App/app.h"
#include "../rendering/ShapeRenderer.h"
MenuScene::MenuScene()
{
	this->m_scene_type = scene_type::menu;

	Load();
}

MenuScene::~MenuScene()
{
}

void MenuScene::Render()
{
	App::Print(50, 700, std::string("SHOOT THE GREEN SQUARES").c_str(), 0, 1, 0, GLUT_BITMAP_HELVETICA_12);
	App::Print(50, 650, std::string("AVOID THE RED SQUARES").c_str(), 1, 0, 0, GLUT_BITMAP_HELVETICA_12);
	App::Print(50, 600, std::string("PURPLE SQUARES CAN BE BROKEN WITH REGULAR PROJECTILES").c_str(), 1, 0, 1, GLUT_BITMAP_HELVETICA_12);
	App::Print(50, 550, std::string("WHITE SQUARES CAN BE BROKEN WITH BOMBS (WATCH OUT FOR RED AND GREEN SQUARES THOUGH)").c_str(),1, 1, 1, GLUT_BITMAP_HELVETICA_12);
	App::Print(WINDOW_WIDTH / 3.5f, WINDOW_HEIGHT / 2, std::string("TURRET: the game where you're a turret").c_str(), 1, 1, 1, GLUT_BITMAP_TIMES_ROMAN_24);
	App::Print(WINDOW_WIDTH / 3.5f, WINDOW_HEIGHT / 2 - 50, std::string("[Press [ENTER] to continue...").c_str(), 1, 1, 1, GLUT_BITMAP_HELVETICA_18);
	App::Print(300, 100, std::string("CONTROLS: Press [1] for bullets | Press [2] for bombs | Press [SHIFT] to detonate bomb ").c_str());



}

void MenuScene::Update(float deltaTime)
{
}

void MenuScene::OnLoad()
{
	Scene::OnLoad();
}

void MenuScene::OnDestroy()
{
	Scene::OnDestroy();
}

void MenuScene::Load()
{
	Scene::Load();
}

void MenuScene::Destroy()
{
	Scene::Destroy();
}
