#pragma once
#include "../App/App.h"
constexpr int _WINDOW_WIDTH = APP_VIRTUAL_WIDTH;
constexpr int _WINDOW_HEIGHT = APP_VIRTUAL_HEIGHT;
//extern int WINDOW_HEIGHT;
constexpr int MINIMAP_CELL_SIZE = 10;
constexpr int MAP_HEIGHT = 24;
constexpr int MAP_WIDTH = 24;
constexpr int MAP_SIZE = MAP_HEIGHT * MAP_WIDTH;
//constexpr int MAP_CELL_SIZE = 16;
constexpr int MAP_CELL_SIZE = _WINDOW_HEIGHT / MAP_HEIGHT;

