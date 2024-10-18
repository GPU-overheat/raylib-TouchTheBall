#include "ttb.h"


void write_gui(Vector2 *pos, float speed, int count, int highscore, float timer, bool display_gui)
{
    if (display_gui)
    {
        DrawText(TextFormat("pos x: %d", (int)pos->x), 100, 200, 20, GRAY);
        DrawText(TextFormat("pos y: %d", (int)pos->y), 100, 230, 20, GRAY);
    }
    DrawText(TextFormat("speed: %d", (int)speed - (int)BASE_SPEED), 100, 260, 20, GRAY);
    DrawText(TextFormat("count: %d", count), 100, 290, 20, GRAY);
    DrawText(TextFormat("highest: %d", highscore), 100, 350, 20, GRAY);
    DrawText(TextFormat("timer: %.1f", timer), 100, 320, 20, GRAY);
}

void move_input(Vector2 *pos, int screenWidth, int screenHeight, float radius, float speed)
{
    float delta = GetFrameTime();

    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && pos->x < screenWidth - radius)
    {
      pos->x += speed * delta;
    }
    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && pos->x > radius)
    {
      pos->x -= speed * delta;
    }
    if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && pos->y < screenHeight - radius)
    {
      pos->y += speed * delta;
    }
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && pos->y > radius)
    {
      pos->y -= speed * delta;
    }
}

