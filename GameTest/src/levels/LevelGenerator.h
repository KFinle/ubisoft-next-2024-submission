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

// Used to generate random map layouts.
// 
// Generation is handled done using a rough Cellular Automata-based system
class LevelGenerator
{

public:
	std::vector<std::vector<int>> map;

	// Percentages of spawning a given cell type 
	// note: these are the values to subtract from 100 
	int floor_spawn_rate = 50;
	int breakable_spawn_rate = 90;
	int death_spawn_rate = 98;

	void GenerateMap();
	int NumberOfNearWalls(int x, int y);
	void FixMap();
	void SpawnWinSquare();
	void CreateRooms();

	// data members 
	int number_of_generations = 5;
	int max_rooms = 1;
	int min_rooms = 0;
	int max_room_width = 3;
	int min_room_width = 2;
	int max_room_height = 4;
	int min_room_height = 3;

	std::vector<int> genned_level = {};
};

