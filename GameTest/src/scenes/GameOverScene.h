#pragma once
#include "Scene.h"

// GameOver Scene
class GameOverScene : public Scene
{
public:
	GameOverScene();
	~GameOverScene();
	void Render() override;
	void Update(float delta_time) override;
	void OnLoad() override;
	void OnDestroy() override;
	void Load() override;
	void Destroy() override;
};
