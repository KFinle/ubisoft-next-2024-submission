#include "stdafx.h"
#include "time.h"
#include "LevelGenerator.h"

void LevelGenerator::GenerateMap()
{
	int seed = time(NULL);

	srand(seed);
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			map[h][w] = Cell::EMPTY;
			if (rand() % 100 > floor_spawn_rate)
			{
				map[h][w] = Cell::WALL;
			}
		}
	}

	for (int generation = 0; generation < number_of_generations; generation++)
	{
		FixMap();
	}
	// Create rooms
	CreateRooms();

	// ensure there's a spawnpoint for the player
// for now, we'll start at centre
	map[MAP_HEIGHT / 2][MAP_WIDTH / 2] = Cell::PLAYER;


	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			genned_level.push_back(map[h][w]);
		}
	}
}

int LevelGenerator::NumberOfNearCells(int x, int y)
{
	int count = 0;
	for (int h = y - 1; h <= y + 1; h++)
	{
		for (int w = x - 1; w <= x + 1; w++)
		{
			if (!(w == x && h == y) && h >= 0 && h < MAP_HEIGHT && w >= 0 && w < MAP_WIDTH)
			{
				if (map[h][w] == Cell::WALL)
				{
					count++;
				}
			}
		}
	}
	return count;
}


void LevelGenerator::FixMap()
{
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			if (map[h][w] == Cell::WALL && NumberOfNearCells(w, h) >= 5)
			{
				map[h][w] = Cell::EMPTY;
			}
			if (map[h][w] == Cell::EMPTY && NumberOfNearCells(w, h) <= 1)
			{
				map[h][w] = Cell::WALL;
			}

			if (w == 0 || w == MAP_WIDTH - 1 || h == 0 || h == MAP_HEIGHT - 1)
			{
				map[h][w] = Cell::WALL;
			}
		}
	}
}

void LevelGenerator::CreateRooms()
{
	int num_rooms = rand() % max_rooms + max_rooms;

	for (int i = 0; i < num_rooms; ++i)
	{
		int room_width = rand() % max_room_width + min_room_width;
		int room_height = rand() % max_room_height + min_room_height;

		int room_x = rand() % (MAP_WIDTH - room_width - 1) + 1;
		int room_y = rand() % (MAP_HEIGHT - room_height - 1) + 1;

		for (int h = room_y; h < room_y + room_height; ++h)
		{
			for (int w = room_x; w < room_x + room_width; ++w)
			{
				map[h][w] = Cell::EMPTY;
			}
		}
	}
}