#include "stdafx.h"
#include "Collider.h"
#include "../App/app.h"

// simple box collision for now 
bool Collider::CheckCollision(const Collider& other) const 
{
    return 
        (
            (position.GetX() + width / 2) > (other.position.GetX() - other.width / 2) &&
            (position.GetX() - width / 2) < (other.position.GetX() + other.width / 2) &&
            (position.GetY() + height / 2) > (other.position.GetY() - other.height / 2) &&
            (position.GetY() - height / 2) < (other.position.GetY() + other.height / 2)
        );
}

// Called every frame 
void Collider::Update(float delta_time)
{
    // look for other colliders
    // probably using the callback setup used on the Projectile class
}

// Checks if a collision with the level has occured
// @param direction_x | scaled to Virtual Window size
// @param direction_y | scaled to Virtual Window size
// @returns Cell type
Cell Collider::CheckWallCollision(int direction_x, int direction_y, Level& level)
{
    //position should be scaled to window size (ie: virtual coords)
    int mappos = (direction_y / MAP_CELL_SIZE) * MAP_WIDTH  + (direction_x / MAP_CELL_SIZE);

    if (mappos >= 0 && mappos < MAP_WIDTH * MAP_HEIGHT)
    {
        Cell cell_type_hit = static_cast<Cell>(level.level_map.at(mappos));
        if (cell_type_hit == Cell::GOAL)         level.goal_found       = mappos;
        if (cell_type_hit == Cell::INSTANTDEATH) level.death_found      = mappos;
        if (cell_type_hit == Cell::BREAKABLE)    level.breakable_found  = mappos;
        return cell_type_hit;
    }
    return EMPTY;
}

// Gets the center position of the collider
Vector3 Collider::GetPosition() const
{
    return position;
}

// Visualize the collider
void Collider::DrawColliderLines() const
{
    const float half_width = width / 2;
    const float half_height = height / 2;

    App::DrawLine(position.GetX() - half_width, position.GetY() + half_height, position.GetX() + half_width, position.GetY() + half_height, 0, 1, 0); // Top line
    App::DrawLine(position.GetX() - half_width, position.GetY() - half_height, position.GetX() + half_width, position.GetY() - half_height, 0, 1, 0); // Bottom line
    App::DrawLine(position.GetX() - half_width, position.GetY() + half_height, position.GetX() - half_width, position.GetY() - half_height, 0, 1, 0); // Left line
    App::DrawLine(position.GetX() + half_width, position.GetY() + half_height, position.GetX() + half_width, position.GetY() - half_height, 0, 1, 0); // Right line

}