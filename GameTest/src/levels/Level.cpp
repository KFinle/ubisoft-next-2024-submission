#include "stdafx.h"
#include "Level.h"
#include "LevelGenerator.h"

std::vector<int> Level::RandomizeLevel()
{
	std::vector<int> random_map;
	LevelGenerator builder;
	builder.GenerateMap();
	random_map = builder.genned_level;
	return random_map;
}

Vector3 Level::GetPositionFromLevelCell(int index)
{
	int x = index % MAP_WIDTH;
	int y = index / MAP_WIDTH;

	// Calculate the screen position
	float x_position = static_cast<float>(x) * MAP_CELL_SIZE;
	float y_position = static_cast<float>(y) * MAP_CELL_SIZE;

	return Vector3(MathUtility::ScaleToNativeWidth(x_position), MathUtility::ScaleToNativeHeight(y_position));
}

void Level::BuildMap()
{
	int x, y;
	float x_offset, y_offset;

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			x_offset = x * MAP_CELL_SIZE;
			y_offset = y * MAP_CELL_SIZE;
			int mappos = y * MAP_WIDTH + x;

			if (mappos >= 0 && mappos < MAP_SIZE)
			{
				switch (level_map.at(mappos))
				{
					case Cell::WALL:
						m_colour.Set(1, 1, 1);
						break;
					case Cell::GOAL:
						m_colour.Set(0.5, 0.1, 1);
						break;
					case Cell::ENEMYNEXUS:
						m_colour.Set(1, 0, 1);
						break;
					case Cell::BREAKABLE:
						m_colour.Set(.8, 1, .1);
						break;
					case Cell::INSTANTDEATH:
						m_colour.Set(1, 0, 0);
						break;
					default:
						m_colour.Set(0, 0, 0);
						break;
				}

				// only need to assess this on first pass
				if (player_spawn == 0)
				{
					if (level_map.at(mappos) == 3)
					{
						this->player_spawn = mappos;
					}
				}
			}

			ShapeRenderer::RenderSquare(x_offset + 1, y_offset, x_offset + MAP_CELL_SIZE - 1, y_offset + MAP_CELL_SIZE - 1, m_colour.r, m_colour.g, m_colour.b);
		}
	}
}

void Level::DrawMapSmall()
{
	int x, y;
	float x_offset, y_offset;

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{

			x_offset = x * MAP_CELL_SIZE * 2;
			y_offset = y * MAP_CELL_SIZE * 2;
			int mappos = y * MAP_WIDTH + x;

			if (mappos >= 0 && mappos < MAP_SIZE)
			{
				if (level_map.at(mappos) == 1)
				{
					m_colour.Set(1, 1, 1);
				}
				else if (level_map.at(mappos) == 2)
				{
					win_square = (y * MAP_WIDTH + x);
					m_colour.Set(0.5, 0.1, 1);
				}
				else m_colour.Set(0.1, 0.1, 0.1);
			}


			ShapeRenderer::RenderSquare(
				(x_offset + 1) / 6, 
				y_offset / 6, 
				(x_offset + MAP_CELL_SIZE * 2 - 1) / 6, 
				(y_offset + MAP_CELL_SIZE * 2 - 1) / 6,
				m_colour.r, m_colour.g, m_colour.b);
		}
	}
}



