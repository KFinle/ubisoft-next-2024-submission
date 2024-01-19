#pragma once
#include "vector"
class LevelGenerator
{
	// https://www.youtube.com/watch?v=TlLIOgWYVpI
//https://www.youtube.com/watch?v=S9QTsf9AUqQ

public:
	enum Cell
	{
		EMPTY, WALL, GOAL, PLAYER
	};

	int map[MAP_HEIGHT][MAP_WIDTH];

	int floor_spawn_rate = 90;
	int number_of_generations = 5;
	void GenerateMap();
	int NumberOfNearCells(int x, int y);

	void FixMap();

	void CreateRooms();
	int max_rooms = 3;
	int min_rooms = 2;
	int max_room_width = 5;
	int min_room_width = 3;
	int max_room_height = 6;
	int min_room_height = 3;
	std::vector<int> genned_level = {};
};

