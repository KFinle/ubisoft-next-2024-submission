#include "Scene.h"
//#include "../objectpools/Pool.h"
//#include "../components/Transform.h"
//#include "../components/Physics.h"
//#include "../components/Component.h"
//#include "../components/Player.h"
//#include "../entities/Entity.h"
#include "../levels/Level.h"
#include "vector"

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

	//std::shared_ptr<Player> player = nullptr;
	std::shared_ptr<Level> level = nullptr;
};
