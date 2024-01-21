#pragma once
#pragma once
#include "../utility/TypeIDGenerator.h"
#include "../components/Component.h"
#include <vector>

using TypeID = uint64_t;
using EntityID = TypeID;

enum EntityAttribute {
    NoAttribute = 0,
    Updatable = 1 << 0,
    Renderable = 1 << 1,
    CastsRays = 1 << 2,
    Collides = 1 << 3,
    Explodes = 1 << 4,
    // Add more attributes as needed
};


class BaseEntity 
{

public:
    BaseEntity() {}
    virtual ~BaseEntity() {}
    virtual void Update(float delta_time) = 0;
    virtual int GetAttributes() const {
        return NoAttribute;
    }
    bool HasAttribute(EntityAttribute attribute) const {
        return (GetAttributes() & static_cast<int>(attribute)) != 0;
    }
};


template <typename... Components>
class Entity 
{
private:
    std::vector<BaseComponent*> m_components;
    EntityID m_id;
    int m_attributes;


public:
    friend class GameplayScene;

    Entity(int attributes = NoAttribute) : m_attributes(attributes) 
    {
        (AddComponent<Components>(), ...);
        m_id = TypeIDGenerator<Entity>::GenerateNewID<Entity>();
    }


    // Constructor with spawn_position parameter
    Entity(Vector3 spawn_position) : Entity() {
        SetSpawnPosition(spawn_position);
    }

    ~Entity()
    {
        for (auto& comp : m_components)
        {
            comp->~BaseComponent();
        }
    }

    void Update(float delta_time)
    {
        for (auto& component : m_components)
        {
            if (component->HasAttribute(Updatable))
            {
                component->Update();
            }
        }
    }

    // Add a component to the entity
    template <typename T>
    void AddComponent() {
        m_components.push_back(new T());
    }

    // Get a component of a specific type
    template <typename T>
    T* GetComponent() const {
        for (auto* component : m_components) {
            Component<T>* derivedComponent = dynamic_cast<Component<T>*>(component);
            if (derivedComponent) {
                return dynamic_cast<T*>(derivedComponent);
            }
        }
        return nullptr;
    }

    // Remove components based on their types
    template <typename T>
    void RemoveComponent() {
        auto i = std::remove_if(m_components.begin(), m_components.end(),
            [](BaseComponent* component) {
                return dynamic_cast<Component<T>*>(component) != nullptr;
            });

        for (auto to_delete = i; to_delete != m_components.end(); to_delete) {
            delete* to_delete;
        }

        m_components.erase(it, m_components.end());
    }

    // Remove multiple components based on their types
    template <typename... Ts>
    void RemoveComponents() {
        // Iterate through each type in the template parameter pack
        (RemoveComponent<Ts>(), ...);
    }

    // Set spawn position in the existing Transform component if it exists
    void SetSpawnPosition(Vector3 spawn_position) {
        Transform* transform = GetComponent<Transform>();
        if (transform) {
            transform->SetPosition(spawn_position);
        }
    }

    // Check if the entity has a specific component
    template <typename T>
    bool HasComponent() const {
        return GetComponent<T>() != nullptr;
    }

};
