#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    Vector2 ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};

    InitWindow(screenWidth, screenHeight, "Find the peacock");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            ballPosition.x += 2.0f;
        }

        if (IsKeyDown(KEY_LEFT))
        {
            ballPosition.x -= 2.0f;
        }

        if (IsKeyDown(KEY_UP))
        {
            ballPosition.y -= 2.0f;
        }

        if (IsKeyDown(KEY_DOWN))
        {
            ballPosition.y += 2.0f;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Mova o pavão!", 10, 10, 20, DARKGRAY);

        DrawCircleV(ballPosition, 50, MAROON);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}