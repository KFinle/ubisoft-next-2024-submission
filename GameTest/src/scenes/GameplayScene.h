#include "Scene.h"
//#include "../objectpools/Pool.h"
//#include "../components/Transform.h"
//#include "../components/Physics.h"
//#include "../components/Component.h"
#include "../components/Player.h"
#include "../entities/Entity.h"
#include "../levels/Level.h"
#include "vector"
#include "memory"
#include "../components/Raycaster.h"


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

	// templated entity creation within scene
	template <typename... Components>
	Entity<Components...>& AddEntity() {
		entities.push_back(std::make_unique<Entity<Components...>>());
		return *static_cast<Entity<Components...>*>(entities.back().get());
	}


private:
	template <class Collider>
	void HandleCollisions();


	std::vector<std::unique_ptr<BaseEntity>> m_entities;
	bool hidemap = false;
	Entity<Player> *player = new Entity<Player>();
	Level* level = nullptr;
	Raycaster* raycaster = nullptr;
};

template<class Collider>
inline void GameplayScene::HandleCollisions()
{
    // Check for collisions with colliders in other entities
    for (auto& entity_ptr : m_entities)
    {
        // Use dynamic_cast to check if the entity is of type Entity<Collider*>
        if (Entity<Collider*>* derived_entity = dynamic_cast<Entity<Collider*>*>(entity_ptr.get()))
        {
            Collider* current_collider = derived_entity->GetComponent<Collider>();

            // Check if the current entity has a collider
            if (current_collider)
            {
                // Iterate over other entities to check for collisions
                for (auto& other_entity_ptr : m_entities)
                {
                    // Avoid self-entity check
                    if (entity_ptr != other_entity_ptr)
                    {
                        // Use dynamic_cast to check if the other entity is of type Entity<Collider*>
                        if (Entity<Collider*>* derived_other_entity = dynamic_cast<Entity<Collider*>*>(other_entity_ptr.get()))
                        {
                            Collider* other_collider = derived_other_entity->GetComponent<Collider>();

                            // Check if the other entity has a collider
                            if (other_collider)
                            {
                                // Check for collisions between the colliders
                                if (current_collider->CheckCollision(*other_collider))
                                {
                                    // Collision detected, handle it here
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
