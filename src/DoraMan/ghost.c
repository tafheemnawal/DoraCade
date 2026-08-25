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

void PickRandomDirection(Ghost *ghost)
{
    int options[4][2] = {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    int validCount = 0;
    int validDirs[4][2];

    for (int i = 0; i < 4; i++)
    {
        int checkRow = ghost->row + options[i][0];
        int checkCol = ghost->col + options[i][1];

        if (!IsWall(checkRow, checkCol))
        {
            validDirs[validCount][0] = options[i][0];
            validDirs[validCount][1] = options[i][1];
            validCount++;
        }
    }

    if (validCount > 0)
    {
        int choice = GetRandomValue(0, validCount - 1);
        ghost->dirRow = validDirs[choice][0];
        ghost->dirCol = validDirs[choice][1];
    }
}

void UpdateGhost(Ghost *ghost, float dt)
{
    float targetX = ghost->targetCol * TILE_SIZE;
    float targetY = ghost->targetRow * TILE_SIZE;

    if (ghost->x == targetX && ghost->y == targetY)
    {
        ghost->row = ghost->targetRow;
        ghost->col = ghost->targetCol;

        PickRandomDirection(ghost);

        int nextRow = ghost->row + ghost->dirRow;
        int nextCol = ghost->col + ghost->dirCol;

        if (!IsWall(nextRow, nextCol))
        {
            ghost->targetRow = nextRow;
            ghost->targetCol = nextCol;
        }
    }

    if (ghost->x < targetX)
    {
        ghost->x += ghost->speed * dt;
        if (ghost->x > targetX) ghost->x = targetX;
    }
    else if (ghost->x > targetX)
    {
        ghost->x -= ghost->speed * dt;
        if (ghost->x < targetX) ghost->x = targetX;
    }

    if (ghost->y < targetY)
    {
        ghost->y += ghost->speed * dt;
        if (ghost->y > targetY) ghost->y = targetY;
    }
    else if (ghost->y > targetY)
    {
        ghost->y -= ghost->speed * dt;
        if (ghost->y < targetY) ghost->y = targetY;
    }
}

void DrawGhost(Ghost *ghost)
{
    float centerX = ghost->x + TILE_SIZE / 2;
    float centerY = ghost->y + TILE_SIZE / 2;
    DrawCircle(centerX, centerY, TILE_SIZE / 2 - 6, RED);
}