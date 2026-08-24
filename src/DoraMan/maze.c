#include "maze.h"
#include <raylib.h>

// Kept private to this file - no other file can see this array directly.
// 1 = wall, 0 = open path
static int maze[MAZE_ROWS][MAZE_COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,1,1,1,0,1,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1},
    {1,0,0,0,1,1,1,0,1,1,0,1,1,1,0,1},
    {1,1,1,0,1,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,1,0,0,0,1,1,1,0,1},
    {1,0,1,1,1,0,1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void DrawMaze(void)
{
    for (int row = 0; row < MAZE_ROWS; row++)
    {
        for (int col = 0; col < MAZE_COLS; col++)
        {
            if (maze[row][col] == 1)
            {
                DrawRectangle(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE, DARKBLUE);
            }
        }
    }
}

int IsWall(int row, int col)
{
    if (row < 0 || row >= MAZE_ROWS || col < 0 || col >= MAZE_COLS)
    {
        return 1; // treat out-of-bounds as a wall
    }
    return maze[row][col] == 1;
}