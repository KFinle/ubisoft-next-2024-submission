#include "stdafx.h"
#include "Level.h"


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

			//x_offset = x * MAP_CELL_SIZE + MAP_OFFSET_X;
			//y_offset = y * MAP_CELL_SIZE + MAP_OFFSET_Y;
			x_offset = x * MAP_CELL_SIZE;
			y_offset = y * MAP_CELL_SIZE;
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
				else if (level_map.at(mappos) == 4)
				{
					win_square = (y * MAP_WIDTH + x);
					m_colour.Set(1, 0, 1);
				}
				//else m_colour.Set(0.1, 0.1, 0.1);
				else m_colour.Set(0, 0, 0);


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
			//ShapeRenderer::RenderShapeWithNPolygons(x_offset + MAP_CELL_SIZE * 4, y_offset + MAP_CELL_SIZE / 2, MAP_CELL_SIZE / 2, m_colour.r, m_colour.g, m_colour.b, 4);

		}
	}
}

void Level::DrawMapBig(Vector3 player_cell)
{
	int current_player_cell = player_cell.GetY() * MAP_WIDTH + player_cell.GetX();
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
				if (current_player_cell == mappos)
				{
					m_colour.Set(1, 0, 1);
				}
				else if (level_map.at(mappos) == 1)
				{
					m_colour.Set(1, 1, 1);
				}
				else if (level_map.at(mappos) == 2)
				{
					win_square = (y * MAP_WIDTH + x);
					m_colour.Set(0.5, 0.1, 1);
				}
				else m_colour.Set(0.1, 0.1, 0.1);

				// only need to assess this on first pass
				if (player_spawn == 0)
				{
					if (level_map.at(mappos) == 3)
					{
						this->player_spawn = mappos;
					}
				}
			}


			ShapeRenderer::RenderSquare(x_offset + 1, y_offset, x_offset + MAP_CELL_SIZE * 2 - 1, y_offset + MAP_CELL_SIZE * 2 - 1, m_colour.r, m_colour.g, m_colour.b);
		}
	}
}



