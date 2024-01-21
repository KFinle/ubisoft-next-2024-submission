#pragma once
#include "vector"
#include "../Globals.h"
enum Cell
{
	EMPTY, 
	WALL,
	GOAL, 
	PLAYER, 
	BORDER, 
	BREAKABLE, 
	INSTANTDEATH, 
};
class LevelGenerator
{
// https://www.youtube.com/watch?v=TlLIOgWYVpI

public:
	std::vector<std::vector<int>> map;
	//int map[MAP_HEIGHT][MAP_WIDTH];

	int floor_spawn_rate = 50;
	int breakable_spawn_rate = 90;
	int death_spawn_rate = 98;

	int number_of_generations = 5;
	void GenerateMap();
	int NumberOfNearWalls(int x, int y);

	void FixMap();

	void SpawnWinSquare();


	void CreateRooms();
	//int max_rooms = 1;
	//int min_rooms = 1;
	//int max_room_width = 4;
	//int min_room_width = 2;
	//int max_room_height = 3;
	//int min_room_height = 4;




	// From when I was trying to do something totally different 
	int max_rooms = 3;
	int min_rooms = 2;
	int max_room_width = 5;
	int min_room_width = 3;
	int max_room_height = 6;
	int min_room_height = 3;

	std::vector<int> genned_level = {};
};

