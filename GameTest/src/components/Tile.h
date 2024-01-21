#pragma once
#include "Component.h"
#include "../rendering/ShapeRenderer.h"
#include "Collider.h"
#include "functional"


struct Tile : public Component<Tile>
{
	Tile() : Component(CollidingComponent | RenderableComponent)
	{
		m_id = TypeIDGenerator<Tile>::GenerateNewID<Tile>();
	}

	//void Update()
};
void Render()
{

}

void SetCollisionCallback(std::function<bool(float, float)> callback)
{
	collision_callback = std::move(callback);
}

ComponentTypeID m_id;
std::function<bool(float, float)> collision_callback;