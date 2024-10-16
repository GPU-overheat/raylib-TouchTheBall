#include "raylib.h"
#include <math.h>

#define BASE_SPEED 800.0f

typedef enum {
    GAME_START,
    GAME_RUNNING,
    GAME_OVER
} GameState;

void move_input(Vector2 *pos, int screenWidth, int screenHeight, float radius, float speed);
void write_gui(Vector2 *pos, float speed, int count, int highscore, float timer, bool display_gui);

int main(void)
{
    const int screenWidth = 1600;
    const int screenHeight = 900;
    int count = 0;
    int highscore = 0;
    float timer = 10.0f;
    float speed = BASE_SPEED;
    bool display_gui = false;
    float pulse = 0.0f;
    GameState gameState = GAME_START;

    bool explosionActive = false;
    float explosionRadius = 0.0f;
    Vector2 explosionCenter = { 0.0f, 0.0f };
    float explosionAlpha = 1.0f;

    InitWindow(screenWidth, screenHeight, "Touch-the-ball");
    SetTargetFPS(60);

    Vector2 pos = { 10.0f, 10.0f };
    Vector2 target = { 400.0f, 300.0f };
    float radius = 30.0f;
    Color mainCircleColor = RED;
    Color dis = BLUE;
    const char* colorName = "RED";

    while (!WindowShouldClose())
    {
        pulse += GetFrameTime();

        if (gameState == GAME_START)
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("WELCOME TO TOUCH THE BALL", screenWidth / 2 - 300, screenHeight / 2 - 100, 40, DARKGRAY);
            DrawText("Move using Arrow Keys or W/A/S/D", screenWidth / 2 - 260, screenHeight / 2 - 30, 30, GRAY);
            DrawText("Press any movement key to start!", screenWidth / 2 - 230, screenHeight / 2 + 40, 30, RED);

            EndDrawing();

            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A) || 
                IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
            {
                gameState = GAME_RUNNING;
            }
        }
        else if (gameState == GAME_RUNNING)
        {
            move_input(&pos, screenWidth, screenHeight, radius, speed);

            if (CheckCollisionCircles(pos, radius, target, radius))
            {
                mainCircleColor = GREEN;
                colorName = "GREEN";
                dis = RAYWHITE;
                count++;
                timer += 0.5f;
                speed += 50;

                explosionActive = true;
                explosionRadius = 0.0f;
                explosionCenter = target;
                explosionAlpha = 1.0f;

                target.x = GetRandomValue(radius, screenWidth - radius);
                target.y = GetRandomValue(radius, screenHeight - radius);
            }
            else
            {
                mainCircleColor = RED;
                colorName = "RED";
                dis = BLUE;
            }

            timer -= GetFrameTime();

            if (timer <= 0.0f)
            {
                gameState = GAME_OVER;
                if (count > highscore)
                {
                    highscore = count;
                }
            }

            if (IsKeyPressed(KEY_SPACE))
            {
                display_gui = !display_gui;
            }

            float pulseRadius = radius + 5.0f * sinf(pulse * 5.0f);

            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawFPS(10, 10);
            write_gui(&pos, speed, count, highscore, timer, display_gui);
            DrawCircle((int)target.x, (int)target.y, pulseRadius, dis);
            DrawCircle((int)pos.x, (int)pos.y, radius, mainCircleColor);

            if (explosionActive)
            {
                explosionRadius += 300.0f * GetFrameTime();
                explosionAlpha -= 1.0f * GetFrameTime();

                for (int i = 0; i < 3; i++)
                {
                    DrawCircleV(explosionCenter, explosionRadius * (0.1f + i * 0.2f), Fade(BLUE, explosionAlpha - i * 0.3f));
                }

                if (explosionAlpha <= 0.0f)
                {
                    explosionActive = false;
                }
            }

            EndDrawing();
        }
        else if (gameState == GAME_OVER)
        {
            BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("GAME OVER", screenWidth / 2 - 150, screenHeight / 2 - 50, 60, RED);
            DrawText(TextFormat("Score: %d", count), screenWidth / 2 - 60, screenHeight / 2 + 30, 40, GRAY);
            DrawText("Press 'R' to restart", screenWidth / 2 - 120, screenHeight / 2 + 100, 30, DARKGRAY);

            EndDrawing();

            if (IsKeyDown(KEY_R))
            {
                pos = (Vector2){ 10.0f, 10.0f };
                target = (Vector2){ 400.0f, 300.0f };
                count = 0;
                timer = 10.0f;
                speed = BASE_SPEED;
                gameState = GAME_RUNNING;
            }
        }
    }

    CloseWindow();
    return 0;
}

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
    float deltaTime = GetFrameTime();

    if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && pos->x < screenWidth - radius)
    {
        pos->x += speed * deltaTime;
    }
    if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && pos->x > radius)
    {
        pos->x -= speed * deltaTime;
    }
    if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && pos->y < screenHeight - radius)
    {
        pos->y += speed * deltaTime;
    }
    if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && pos->y > radius)
    {
        pos->y -= speed * deltaTime;
    }
}

