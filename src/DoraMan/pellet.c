#include "pellet.h"
#include "maze.h"
#include <raylib.h>

// 1 = pellet present, 0 = no pellet (wall or already eaten)
static int pellets[MAZE_ROWS][MAZE_COLS];

void InitPellets(int startRow, int startCol)
{
    for (int row = 0; row < MAZE_ROWS; row++)
    {
        for (int col = 0; col < MAZE_COLS; col++)
        {
            if (IsWall(row, col))
            {
                pellets[row][col] = 0;
            }
            else
            {
                pellets[row][col] = 1;
            }
        }
    }

    // No pellet on the player's starting tile
    pellets[startRow][startCol] = 0;
}

void DrawPellets(void)
{
    for (int row = 0; row < MAZE_ROWS; row++)
    {
        for (int col = 0; col < MAZE_COLS; col++)
        {
            if (pellets[row][col] == 1)
            {
                float centerX = col * TILE_SIZE + TILE_SIZE / 2;
                float centerY = row * TILE_SIZE + TILE_SIZE / 2;
                DrawCircle(centerX, centerY, 5, WHITE);
            }
        }
    }
}

int CollectPellet(int row, int col)
{
    if (pellets[row][col] == 1)
    {
        pellets[row][col] = 0;
        return 1;
    }
    return 0;
}