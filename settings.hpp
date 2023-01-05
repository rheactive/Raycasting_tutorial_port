#ifndef SETTINGS_HPP // include guard
#define SETTINGS_HPP

const float PI = 3.14159265359f;

// main window settings
const int WINDOW_WIDTH = 2400;
const int WINDOW_HEIGHT = 1350;
const int TARGET_FPS = 60;
const char * WINDOW_TITLE = "Raycasting tutorial";

// map related constant
const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 16;
const int MINI_MAP_WIDTH = 800;
const int MINI_MAP_HEIGHT = 800;
const int MINI_MAP_X = WINDOW_WIDTH - MINI_MAP_WIDTH;
const int MINI_MAP_Y = 0;
const int TILE_WIDTH = MINI_MAP_WIDTH / MAP_WIDTH;
const int TILE_HEIGHT = MINI_MAP_HEIGHT / MAP_HEIGHT;

// player related constants
const float PLAYER_X = 9.5f;
const float PLAYER_Y = 5.5f;
const float PLAYER_ANGLE = 0.0f;
const float PLAYER_SPEED = 2.5f;
const float PLAYER_ROT_SPEED = 2.5f;
const float PLAYER_RADIUS = 0.35f;

#endif /* SETTINGS_HPP */