#include <raylib.h>
#include "maze.h"

int main(void)
{
    const int screenWidth = MAZE_COLS * TILE_SIZE;
    const int screenHeight = MAZE_ROWS * TILE_SIZE;

    InitWindow(screenWidth, screenHeight, "DoraMan Test");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawMaze();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}