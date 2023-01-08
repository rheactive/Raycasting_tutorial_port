#ifndef SETTINGS_HPP // include guard
#define SETTINGS_HPP

#include <cmath>

const float PI = 3.14159265359f;
const float DEG = PI / 180.f;

// main window settings
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int TILE_TEXTURE_SIZE = 64;
const int SPRITE_TEXTURE_SIZE = 128;
const int HALF_WIDTH = WINDOW_WIDTH / 2;
const int HALF_HEIGHT = WINDOW_HEIGHT / 2;
const int TARGET_FPS = 60;
const char *WINDOW_TITLE = "Raycasting tutorial";

// map related constants
const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 16;
const int MINI_MAP_WIDTH = 320;
const int MINI_MAP_HEIGHT = 320;
const int MINI_MAP_X = WINDOW_WIDTH - MINI_MAP_WIDTH - 20;
const int MINI_MAP_Y = 20;
const int TILE_WIDTH = MINI_MAP_WIDTH / MAP_WIDTH;
const int TILE_HEIGHT = MINI_MAP_HEIGHT / MAP_HEIGHT;

// player related constants
const float PLAYER_X = 9.5f;
const float PLAYER_Y = 5.5f;
const float PLAYER_ANGLE = 0.0f;
const float PLAYER_SPEED = 5.0f;
const float PLAYER_ROT_SPEED = 2.0f;
const float PLAYER_RADIUS = 0.35f;
const float BOB_FREQUENCY = 3.f;
const float BOB_MAGNITUDE = 0.05f;

// raycasting related constants
const float PLAYER_FOV = PI / 2.5f;
const float HALF_FOV = PLAYER_FOV / 2.0f;
const float SCREEN_DISTANCE = HALF_WIDTH / tan(HALF_FOV);
const float STEP_SIZE = 2.0f;
const float TOLERANCE = 0.0001f;
const float MAX_DISTANCE = 20.0;
const int RAYS_NUMBER = WINDOW_WIDTH / STEP_SIZE;
const float ANGLE_STEP = PLAYER_FOV / RAYS_NUMBER; // approximate, we use variable angle step
const int MINI_MAP_RAYS_NUMBER = RAYS_NUMBER / 4;

const float STEP_REL = STEP_SIZE / SCREEN_DISTANCE;
const float PLAYER_Z = 0.5f;
const float FLOOR_SIZE = MAP_WIDTH * 1.f;
const float FLOOR_TEXTURE_SIZE = 1024.0f;

#endif /* SETTINGS_HPP */