#include <raylib.h>
#include "DoraRush/player.h"
#include "DoraRush/collision.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "DoraCade");

    Player player;
    Pipe pipe;

    InitPlayer(&player, screenWidth, screenHeight);
    InitPipe(&pipe, screenWidth);
    SetTargetFPS(60);

    int gameOver = 0;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if (!gameOver)
        {
            // Update
            UpdatePlayer(&player, screenWidth, screenHeight, dt);
            UpdatePipe(&pipe, screenWidth, dt);

            // All collisions in one place
            if (CheckPipeCollision(&player, &pipe) ||
                CheckCeilingCollision(&player) ||
                CheckFloorCollision(&player, screenHeight))
            {
                gameOver = 1;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawPlayer(&player);
        DrawPipe(&pipe, screenHeight);

        if (gameOver)
        {
            DrawText("GAME OVER", 500, 300, 40, RED);
        }

        DrawFPS(10, 10);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}