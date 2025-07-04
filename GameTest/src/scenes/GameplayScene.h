#pragma once
#include "Scene.h"
#include "memory"
#include "vector"
#include "../components/Player.h"
#include "../entities/Entity.h"
#include "../levels/Level.h"
#include "../components/Raycaster.h"

// Scene used for main gameplay loop
class GameplayScene : public Scene
{
public:
	GameplayScene();
	~GameplayScene();
	void Render() override;
	void Update(float delta_time) override;
	void OnLoad();
	void OnDestroy();
	void Load();
	void Destroy();
	void CheckLevelState(float delta_time);
	void TransitionToGameOver(float delta_time);

	// templated Entity creation within scene
	template <typename... Components>
	Entity<Components...>& AddEntity() {
		entities.push_back(std::make_unique<Entity<Components...>>());
		return *static_cast<Entity<Components...>*>(entities.back().get());
	}

	// start with Player Entity
	Entity<Player> *player = new Entity<Player>();
	int levels_cleared = 0;

private:
	std::vector<BaseEntity*> m_entities;
	Level* level = nullptr;
	Raycaster* raycaster = nullptr;
	bool hidemap = false;
	float transition_time = 1;
};

