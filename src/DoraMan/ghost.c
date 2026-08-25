#include "ghost.h"
#include "maze.h"
#include <raylib.h>

void InitGhost(Ghost *ghost, int startRow, int startCol)
{
    ghost->row = startRow;
    ghost->col = startCol;
    ghost->targetRow = startRow;
    ghost->targetCol = startCol;

    ghost->x = startCol * TILE_SIZE;
    ghost->y = startRow * TILE_SIZE;

    ghost->dirRow = 0;
    ghost->dirCol = 0;

    ghost->speed = 120.0f;
}

void DrawGhost(Ghost *ghost)
{
    float centerX = ghost->x + TILE_SIZE / 2;
    float centerY = ghost->y + TILE_SIZE / 2;
    DrawCircle(centerX, centerY, TILE_SIZE / 2 - 6, RED);
}