#include "stdafx.h"
#include "Raycaster.h"
#include "../rendering/ShapeRenderer.h"
//#include "App/main.h"

/**
* Renders the 2D ray visible on the minimap
*
*/
void Raycaster::RenderRays()
{
    for (const auto r : rays)
    {
        // Draw the original ray
        App::DrawLine(r.start_x, r.start_y, r.end_x, r.end_y, 0.0f, 0.3f, 0.3f);

        // mark the impact
        float marksize = 3;
        ShapeRenderer::RenderSquare(r.end_x - marksize / 2, r.end_y - marksize / 2, r.end_x + marksize / 2, r.end_y + marksize / 2, 1, 0, 1);
    }
}


/**
* Renders the 3D simulation
* @param level -- reference to the current level
*/
void Raycaster::Render3D()
{
    int dof = 0;
    for (int i = 0; i < rays.size(); i++)
    {
        if (dof < max_steps)
        {
            // correct fish-eye
            float corrected_distance = rays[i].distance * cos(MathUtility::DegreeToRadians(rays[i].correction_factor));
            float wall_height = cell_render_size * (static_cast<float>(WINDOW_HEIGHT) / corrected_distance);

            // clamp wall height
            if (wall_height > WINDOW_HEIGHT)
            {
                wall_height = WINDOW_HEIGHT;
            }

            // Calculate illumination based on distance
            float illumination = 1.0f - (rays[i].distance / max_distance);

            // Calculate line height and position
            float vertical_line_offset = (WINDOW_HEIGHT - wall_height) / 2;
            float start_x = i * (WINDOW_WIDTH / num_rays);
            float end_x = (i + 1) * (WINDOW_WIDTH / num_rays);
            float start_y = vertical_line_offset;
            float end_y = vertical_line_offset + wall_height;

            if (rays[i].goal)
            {
                App::DrawLine(start_x, start_y, end_x, end_y, 0 * illumination, 1 * illumination, 0* illumination);
            }
            else if (rays[i].hazard)
            {
                App::DrawLine(start_x, start_y, end_x, end_y, 1 * illumination, 0, 0.4 * illumination);
            }
            else if (rays[i].breakable)
            {
                App::DrawLine(start_x, start_y, end_x, end_y, 1 * illumination, 0, 1 * illumination);
            }
            else
            {
				App::DrawLine(start_x, start_y, end_x, end_y, 0, 0.8f * illumination, 0.8f * illumination);
            }
        }
    }
}


/**
* Casts rays from the player and calculates the distance each ray took to hit an obstacle
* Currently, this requires a Player Component. However, this should be refactored to allow
* any entity to cast rays
* @param player -- reference to the player
* @param level -- reference to the current level
* @return vector containing each calculated ray
*/

std::vector<ray> Raycaster::CalculateRays(const Entity<Player>& player_entity, Level* level)
{
    const Player* player = player_entity.GetComponent<Player>();

    std::vector<ray> calculated_rays;
    Vector3 player_pos = Vector3::ScaledToScreen(player->transform.position);

    // field of view
    float player_angle = player->transform.direction_angle;
    float fov_start = -fov_degrees / 2.0f;
    float angle_increment = fov_degrees / static_cast<float>(num_rays);
    float start_angle = player_angle - fov_start;

    // ensure rays are inline with the rendering of the 2d map
    float level_offset_x = MAP_OFFSET_X;
    float level_offset_y = MAP_OFFSET_Y;


    for (int i = 0; i < num_rays; ++i)
    {
        // initialized ray values
        float current_angle = start_angle - angle_increment * static_cast<float>(i);
        float ray_angle = MathUtility::ModDegrees(current_angle);
        float ray_x_offset = cosf(MathUtility::DegreeToRadians(ray_angle));
        float ray_y_offset = sinf(MathUtility::DegreeToRadians(ray_angle));
        float rx = player_pos.GetX();
        float ry = player_pos.GetY();
        int dof = 0;
        float distance = 0.0f;
        bool goal_found = false;
        bool hazard_found = false;
        bool breakable_found = false;

        // Continue calculating until we hit a collision
        // or we have gone too far. Currently, the distance
        // allowed if extremely high for line-of-sight reasons.
        // Modify as needed to create the effect you're looking for
        while (dof < max_steps && distance < max_distance)
        {
            int mx = static_cast<int>(rx / MAP_CELL_SIZE);
            int my = static_cast<int>(ry / MAP_CELL_SIZE);
            int mp = my * MAP_WIDTH + mx;

            if (mp >= 0 && mp < MAP_WIDTH * MAP_HEIGHT)
            {
                // determine the type of hit that occurred (for 3d rendering)
                if (level->level_map.at(mp) == Cell::WALL)
                {
                    break;
                }
                if (level->level_map.at(mp) == Cell::GOAL)
                {
                    goal_found = true;
                    break;
                }
                if (level->level_map.at(mp) == Cell::BREAKABLE)
                {
                    breakable_found = true;
                    break;
                }
                if (level->level_map.at(mp) == Cell::INSTANTDEATH)
                {
                    hazard_found = true;
                    break;
                }
            }

            // Check for diagonal movement and handle it
            int prev_mx = static_cast<int>((rx - ray_x_offset) / MAP_CELL_SIZE);
            int prev_my = static_cast<int>((ry - ray_y_offset) / MAP_CELL_SIZE);

            // Check if the previous and current cells are diagonally adjacent
            if ((prev_mx != mx) && (prev_my != my))
            {
                // Pretend the ray hit one of the two diagonal cells
                int diag_mp1 = my * MAP_WIDTH + prev_mx;
                int diag_mp2 = prev_my * MAP_WIDTH + mx;

                if (diag_mp1 >= 0 && diag_mp1 < MAP_WIDTH * MAP_HEIGHT && (diag_mp2 >= 0 && diag_mp2 < MAP_WIDTH * MAP_HEIGHT))
                {
                    if (level->level_map.at(diag_mp1) == Cell::WALL || level->level_map.at(diag_mp2) == Cell::WALL)
                    {
                        break;
                    }
                    if (level->level_map.at(diag_mp1) == Cell::GOAL || level->level_map.at(diag_mp2) == Cell::GOAL)
                    {
                        goal_found = true;
                        break;
                    }
                    if (level->level_map.at(diag_mp1) == Cell::INSTANTDEATH || level->level_map.at(diag_mp2) == Cell::INSTANTDEATH)
                    {
                        hazard_found = true;
                        break;
                    }
                }
            }
            // Increment distance if no collision
            distance += 1.0f;

            // Move to the next step
            rx += ray_x_offset;
            ry += ray_y_offset;
            dof++;
        }

        // This could be condensed, but while I'm learning I'd prefer to be very explicit
        ray ray;
        ray.start_x = player_pos.GetX();
        ray.end_x = rx;
        ray.start_y = player_pos.GetY();
        ray.end_y = ry;
        ray.angle = ray_angle;
        ray.player_angle = player_angle;
        ray.distance = distance;
        ray.goal = goal_found;
        ray.hazard = hazard_found;
        ray.breakable = breakable_found;
        ray.correction_factor = MathUtility::ModDegrees(player_angle - ray_angle);
        calculated_rays.push_back(ray);
    }
    return calculated_rays;
}

