#include "stdafx.h"
#include "Collider.h"
#include "../App/app.h"

// simple box collision for now 
bool Collider::CheckCollision(const Collider& other) const 
{
    return (
        (position.GetX() + width / 2) > (other.position.GetX() - other.width / 2) &&
        (position.GetX() - width / 2) < (other.position.GetX() + other.width / 2) &&
        (position.GetY() + height / 2) > (other.position.GetY() - other.height / 2) &&
        (position.GetY() - height / 2) < (other.position.GetY() + other.height / 2)
        );
}

bool Collider::CheckWallCollision(int direction_x, int direction_y, Level& level)
{
    
    //position should be scaled to window size (ie: virtual coords)
    int mappos = (direction_y / MAP_CELL_SIZE) * MAP_WIDTH  + (direction_x / MAP_CELL_SIZE);
    if (mappos >= 0 && mappos < MAP_SIZE)
    {
        if (level.level_map.at(mappos) >= 0 && level.level_map.at(mappos) < MAP_SIZE)
        {
            if (level.level_map.at(mappos) == 1)
            {
                return true;
            }
        }
        return false;
    }
}

void Collider::DrawColliderLines()
{
    const float half_width = width / 2;
    const float half_height = height / 2;

    App::DrawLine(position.GetX() - half_width, position.GetY() + half_height, position.GetX() + half_width, position.GetY() + half_height, 0, 1, 0); // Top line
    App::DrawLine(position.GetX() - half_width, position.GetY() - half_height, position.GetX() + half_width, position.GetY() - half_height, 0, 1, 0); // Bottom line
    App::DrawLine(position.GetX() - half_width, position.GetY() + half_height, position.GetX() - half_width, position.GetY() - half_height, 0, 1, 0); // Left line
    App::DrawLine(position.GetX() + half_width, position.GetY() + half_height, position.GetX() + half_width, position.GetY() - half_height, 0, 1, 0); // Right line

}