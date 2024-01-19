#pragma once
#include "Scene.h"
class MenuScene : public Scene
{
public:
	MenuScene();
	~MenuScene();
	void Render() override;
	void Update(float delta_time) override;
	void OnLoad() override;
	void OnDestroy() override;
	void Load() override;
	void Destroy() override;
};
