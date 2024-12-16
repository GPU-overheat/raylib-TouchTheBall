#ifndef TTB_H
#define TTB_H

#include "raylib.h"
#include "math.h"

#define BASE_SPEED 800.0f
#define SCREEN_W 1600
#define SCREEN_H 900

typedef enum
{
    GAME_START,
    GAME_RUNNING,
    GAME_OVER
} GameState;


void startWindow();
void move_input(Vector2 *pos, int screenWidth, int screenHeight, float radius, float speed);
void write_gui(Vector2 *pos, float speed, int count, int highscore, float timer, bool display_gui);

#endif
