#pragma once
#include <string>

// Window size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

// Ball settings
const int BALL_RADIUS = 10;
const float SPEED_FACTOR = 0.10f;
const float BOUNCE_DAMPING = 0.8f;

// Directional Indicator Settings
const float LINE_LENGTH = 50.0f;

// Level settings
const std::string TILE_MAP_PATH = "assets/levels/level1.map";
const int TILE_SIZE = 32;
const int COLLISION_TILE = 1;
const int WALKABLE_TILE = 0;