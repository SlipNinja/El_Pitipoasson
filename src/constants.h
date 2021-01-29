#include "../dep/raylib/raylib.h"

#ifndef CONSTANTS_H
#define CONSTANTS_H

static const float MAX_LIFE = 100.0f;
static const float MAX_HUNGER = 100.0f;
static const float STARTING_MONEY = 0.0f;

static const Vector2 POS_UI = {20.0f, 20.0f};

static const float LIFE_REGEN = 0.01f;
static const float LIFE_DEGEN = 0.05f;
static const float HUNGER_DEGEN = 0.02f;

static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 720;
static const char* SCREEN_TITLE = "EL PITIPOASSON";

static const int FPS = 60;
static const int FRAMES_FOR_ITEM = 2*FPS;

static const int SCALE_MIN = 8;
static const int SCALE_MAX = 16;

static const int SPEED_MIN = 4;
static const int SPEED_MAX = 10;

static const int RADIUS_OFFSET = 50;
static const int BASE_STRENGHT = 10;

#endif //CONSTANTS_H