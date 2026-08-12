#include "pacplayer.h"
#include "maze.h"
#include <raylib.h>

void InitPacPlayer(PacPlayer *pac)
{
    pac->row = 1;
    pac->col = 1;
    pac->x = pac->col * TILE_SIZE;
    pac->y = pac->row * TILE_SIZE;
}

void DrawPacPlayer(PacPlayer *pac)
{
    float centerX = pac->x + TILE_SIZE / 2;
    float centerY = pac->y + TILE_SIZE / 2;
    DrawCircle(centerX, centerY, TILE_SIZE / 2 - 6, YELLOW);
}