#include <raylib.h>
#include "maze.h"
#include "pacplayer.h"
#include "pellet.h"

int main(void)
{
    const int screenWidth = MAZE_COLS * TILE_SIZE;
    const int screenHeight = MAZE_ROWS * TILE_SIZE;

    InitWindow(screenWidth, screenHeight, "DoraMan Test");
    SetTargetFPS(60);

    PacPlayer pac;
    InitPacPlayer(&pac);
    InitPellets(pac.row, pac.col);

    int score = 0;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        UpdatePacPlayer(&pac, dt);

        if (CollectPellet(pac.row, pac.col))
        {
            score += 10;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawMaze();
        DrawPellets();
        DrawPacPlayer(&pac);

        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}