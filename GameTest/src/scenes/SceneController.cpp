#include "stdafx.h"
#include "SceneController.h"
#include "GameplayScene.h"
#include "MenuScene.h"

SceneController::SceneController()
{
	// intialize time
	m_start_time = std::chrono::steady_clock::now();
	m_current_time = m_start_time;
	m_previous_time = m_start_time;
	m_elapsed_time = m_current_time - m_start_time;
}

void SceneController::SetAllTime()
{
}

float SceneController::GetDeltaTime()
{
	return m_delta_time;
}

std::chrono::duration<float> SceneController::GetElapsedTime() const
{
	return m_elapsed_time;
}

void SceneController::SetCurrentTime()
{
	m_current_time = std::chrono::steady_clock::now();
}

void SceneController::Update(float deltaTime)
{
	m_current_time = std::chrono::steady_clock::now();
	m_elapsed_time = m_current_time - m_start_time;
	m_delta_time = deltaTime / 1000;
	m_previous_time = m_current_time;


	if (current_scene != nullptr)
	{
		current_scene->Update(m_delta_time);

		if (current_scene->m_scene_type == scene_type::menu)
		{
			if (App::IsKeyPressed(APP_PAD_EMUL_START))
			{
				LoadScene(scene_type::gameplay);
			}
		}

		if (current_scene->m_scene_type == scene_type::gameplay)
		{

			if (current_scene->scene_ended)
			{
				LoadScene(scene_type::menu);
			}
		}
	}
}

void SceneController::OnDestroy()
{
	current_scene->Destroy();
}

void SceneController::RenderScene()
{
	if (current_scene != nullptr)
	{
		current_scene->Render();
	}
}

void SceneController::Destroy()
{
	OnDestroy();
}


void SceneController::LoadScene(scene_type type)
{
	if (current_scene != nullptr)
	{
		current_scene->Destroy();
		delete current_scene;
		current_scene = nullptr;
	}

	switch (type)
	{
	case menu:
		current_scene = new MenuScene();
		break;
	case gameplay:
		current_scene = new GameplayScene();
		break;
	case gameover:
		break;
	default:
		break;
	}
}