#pragma once
#include "../App/app.h"
#include "../App/main.h"

/////////////////////////////////////////////////////////////////////////////////////
// WARNING: Changing these settings could have disastrous effects across the game! //
// Be careful :)																   //
/////////////////////////////////////////////////////////////////////////////////////

struct GlobalSettings
{

	static GlobalSettings* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GlobalSettings();
		}
		return instance;

	}

	static void GlobalSettings::SetMapAttributes(int width, int height, int cell_size)
	{
		SetMapWidth(width);
		SetMapHeight(height);
		SetMapCellSize(cell_size);
		MAP_SIZE = MAP_HEIGHT * MAP_WIDTH;
		MAP_CELL_SIZE = _WINDOW_HEIGHT / MAP_HEIGHT;
		MAP_OFFSET_X = MAP_CELL_SIZE * 3;
	}

	static int _WINDOW_WIDTH;
	static int _WINDOW_HEIGHT;
	static int MAP_HEIGHT;
	static int MAP_WIDTH;
	static int MAP_SIZE;
	static int MAP_CELL_SIZE;
	static int MAP_OFFSET_X;
	static int MAP_OFFSET_Y;


private:
	static GlobalSettings* instance;
	GlobalSettings() {}
	static void GlobalSettings::SetMapHeight(int height)
	{
		MAP_HEIGHT = height;
	}
	static void GlobalSettings::SetMapWidth(int width)
	{
		MAP_WIDTH = width;
	}
	static void GlobalSettings::SetMapCellSize(int cell_size)
	{
		MAP_CELL_SIZE = cell_size;
	}
};

static int _WINDOW_WIDTH				= WINDOW_WIDTH;
static int _WINDOW_HEIGHT				= WINDOW_HEIGHT;
static int MAP_HEIGHT					= 10;
static int MAP_WIDTH					= 13;
static int MAP_SIZE						= MAP_HEIGHT * MAP_WIDTH;
static int MAP_CELL_SIZE				= _WINDOW_HEIGHT / MAP_HEIGHT;
static int MAP_OFFSET_X					= MAP_CELL_SIZE * 3;
static int MAP_OFFSET_Y					= 0;
