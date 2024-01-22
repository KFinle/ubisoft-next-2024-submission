#pragma once	
#include <iostream>
#include <chrono>
#include <vector>
#include "../App/app.h"
#include "Scene.h"

// Manages the state of scenes in the game
class SceneController
{
public:
	SceneController();
	void SetAllTime();
	void SetCurrentTime();
	void Update(float delta_time);
	void OnDestroy();
	void RenderScene();
	void Destroy();
	void LoadScene(scene_type type);
	float GetDeltaTime();
	std::chrono::duration<float> GetElapsedTime() const;

private:
	float m_delta_time;
	Scene* current_scene;
	std::chrono::duration<float> m_elapsed_time;
	std::chrono::time_point<std::chrono::steady_clock> m_start_time;
	std::chrono::time_point<std::chrono::steady_clock> m_current_time;
	std::chrono::time_point<std::chrono::steady_clock> m_previous_time;
};

