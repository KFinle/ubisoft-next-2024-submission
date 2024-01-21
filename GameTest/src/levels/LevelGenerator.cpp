#include "stdafx.h"
#include "time.h"
#include "LevelGenerator.h"
#include "../scenes/GameplayScene.h"

void LevelGenerator::GenerateMap()
{
	map.resize(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, Cell::EMPTY));
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
			if (rand() % 100 > breakable_spawn_rate)
			{
				map[h][w] = Cell::BREAKABLE;
			}
			if (rand() % 100 > death_spawn_rate)
			{
				map[h][w] = Cell::INSTANTDEATH;
			}
		}
	}

	for (int generation = 0; generation < number_of_generations; generation++)
	{
		FixMap();
	}
	// Create rooms
	CreateRooms();

	// Spawn victoy squares
	SpawnWinSquare();

	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			genned_level.push_back(map[h][w]);
		}
	}
}

int LevelGenerator::NumberOfNearWalls(int x, int y)
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

			// if there are too many walls 
			if (map[h][w] == Cell::WALL && NumberOfNearWalls(w, h) >= 4)
			{
				map[h][w] = Cell::EMPTY;
			}

			// if there aren't enough walls 
			if (map[h][w] == Cell::EMPTY && NumberOfNearWalls(w, h) <= 1)
			{
				map[h][w] = Cell::WALL;
			}

			// ensure no walls too close to player
			if ( w == 1 || w == 2 )
			{
				map[h][w] = Cell::EMPTY;
			}

			// borders
			if ( w == 0 || h == 0 || h == MAP_HEIGHT - 1 || w == MAP_WIDTH - 1)
			{
				map[h][w] = Cell::BORDER;
			}

			// player spawn point
			if (w == 2 && h == MAP_HEIGHT / 2)
			{
				map[h][w] = Cell::PLAYER;
			}
		}
	}
}



void LevelGenerator::SpawnWinSquare()
{
	int numVictorySquares = 1;

	for (int i = 0; i < numVictorySquares; i++)
	{
		int win_square_x = rand() % (MAP_WIDTH - 2) + 1;
		int win_square_y = rand() % (MAP_HEIGHT - 2) + 1;
		
		// ensure the goal isn't too close to the player
		while (win_square_x < MAP_WIDTH / 3)
		{
			win_square_x = rand() % (MAP_WIDTH - 2) + 1;
		}


		if (map[win_square_y][win_square_x] != Cell::GOAL)
		{
			map[win_square_y][win_square_x] = Cell::GOAL;
		}
		else
		{
			i++;
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
				
				if (!map[h][w] == Cell::PLAYER) map[h][w] = Cell::EMPTY;

			}
		}
	}
}

