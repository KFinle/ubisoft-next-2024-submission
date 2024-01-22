#pragma once
#include "../Globals.h"
enum scene_type
{
	menu, gameplay, gameover
};

// Base scene for all Scenes in the game 
class Scene
{
public:
	virtual ~Scene();
	virtual void Load();
	virtual void Destroy();
	virtual void Render() = 0;
	virtual void Update(float delta_time) = 0;
	scene_type m_scene_type;
	bool scene_ended = false;


protected:
	virtual void OnDestroy() = 0;
	virtual void OnLoad() = 0;
};
