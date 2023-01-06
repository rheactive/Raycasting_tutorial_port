#ifndef SETTINGS_HPP // include guard
#define SETTINGS_HPP

#include <cmath>

const float PI = 3.14159265359f;

// main window settings
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;
const int TILE_TEXTURE_SIZE = 64;
const int HALF_WIDTH = WINDOW_WIDTH / 2;
const int HALF_HEIGHT = WINDOW_HEIGHT / 2;
const int TARGET_FPS = 60;
const char *WINDOW_TITLE = "Raycasting tutorial";

// map related constants
const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 16;
const int MINI_MAP_WIDTH = 480;
const int MINI_MAP_HEIGHT = 480;
const int MINI_MAP_X = WINDOW_WIDTH - MINI_MAP_WIDTH - 30;
const int MINI_MAP_Y = 30;
const int TILE_WIDTH = MINI_MAP_WIDTH / MAP_WIDTH;
const int TILE_HEIGHT = MINI_MAP_HEIGHT / MAP_HEIGHT;

// player related constants
const float PLAYER_X = 9.5f;
const float PLAYER_Y = 5.5f;
const float PLAYER_ANGLE = 0.0f;
const float PLAYER_SPEED = 5.0f;
const float PLAYER_ROT_SPEED = 2.5f;
const float PLAYER_RADIUS = 0.35f;

// raycasting related constants
const float PLAYER_FOV = PI / 2.5f;
const float HALF_FOV = PLAYER_FOV / 2.0f;
const float SCREEN_DISTANCE = HALF_WIDTH / tan(HALF_FOV);
const float STEP_SIZE = 4.0f;
const float TOLERANCE = 0.0001f;
const float MAX_DISTANCE = MAP_WIDTH * 1.5;
const int RAYS_NUMBER = WINDOW_WIDTH / STEP_SIZE;
const int MINI_MAP_RAYS_NUMBER = RAYS_NUMBER / 4;

const float STEP_REL = STEP_SIZE / SCREEN_DISTANCE;

#endif /* SETTINGS_HPP */