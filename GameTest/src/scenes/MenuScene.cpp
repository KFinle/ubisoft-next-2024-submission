#include "stdafx.h"
#include "MenuScene.h"
#include "../App/app.h"
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
	App::Print(_WINDOW_WIDTH / 2, _WINDOW_HEIGHT / 2, "THIS IS THE MENU LOL");
	App::Print(_WINDOW_WIDTH / 2, _WINDOW_HEIGHT - 100, "PRESS [ENTER]");

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
