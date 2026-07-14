#include <raylib.h>
#include "DoraRush/player.h"
#include "DoraRush/pipe.h"

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

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        UpdatePlayer(&player, screenWidth, screenHeight, dt);
        UpdatePipe(&pipe, screenWidth, dt);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawPlayer(&player);
        DrawPipe(&pipe, screenHeight);

        DrawFPS(10, 10);

        DrawText("Welcome to DoraCade!", 420, 300, 40, BLUE);
        DrawText("Level 1", 560, 360, 30, RED);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}