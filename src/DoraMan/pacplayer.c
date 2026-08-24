#include "pacplayer.h"
#include "maze.h"
#include <raylib.h>

void InitPacPlayer(PacPlayer *pac) {
    pac->row = 1;
    pac->col = 1;
    pac->targetRow = 1;
    pac->targetCol = 1;
    
    pac->x = pac->col * TILE_SIZE;
    pac->y = pac->row * TILE_SIZE;
    
    pac->dirRow = 0;
    pac->dirCol = 0;
    
    pac->speed = 200.0f; 
}

void UpdatePacPlayer(PacPlayer *pac, float dt) {
    // 1. Store input whenever key is pressed
    if (IsKeyPressed(KEY_RIGHT)) { pac->dirRow = 0;  pac->dirCol = 1;  }
    if (IsKeyPressed(KEY_LEFT))  { pac->dirRow = 0;  pac->dirCol = -1; }
    if (IsKeyPressed(KEY_UP))    { pac->dirRow = -1; pac->dirCol = 0;  }
    if (IsKeyPressed(KEY_DOWN))  { pac->dirRow = 1;  pac->dirCol = 0;  }

    float targetX = pac->targetCol * TILE_SIZE;
    float targetY = pac->targetRow * TILE_SIZE;

    // 2. Check if Pac-Man has reached his destination tile
    if (pac->x == targetX && pac->y == targetY) {
        pac->row = pac->targetRow;
        pac->col = pac->targetCol;

        // Try moving into the next tile in pac->dir direction
        int nextRow = pac->row + pac->dirRow;
        int nextCol = pac->col + pac->dirCol;

        if (!IsWall(nextRow, nextCol)) {
            pac->targetRow = nextRow;
            pac->targetCol = nextCol;
        }
    }

    // 3. Move smoothly towards target position
    if (pac->x < targetX) {
        pac->x += pac->speed * dt;
        if (pac->x > targetX) pac->x = targetX; // Snap to target if overshot
    }
    else if (pac->x > targetX) {
        pac->x -= pac->speed * dt;
        if (pac->x < targetX) pac->x = targetX;
    }

    if (pac->y < targetY) {
        pac->y += pac->speed * dt;
        if (pac->y > targetY) pac->y = targetY;
    }
    else if (pac->y > targetY) {
        pac->y -= pac->speed * dt;
        if (pac->y < targetY) pac->y = targetY;
    }
}

void DrawPacPlayer(PacPlayer *pac)
{
    float centerX = pac->x + TILE_SIZE / 2;
    float centerY = pac->y + TILE_SIZE / 2;
    DrawCircle(centerX, centerY, TILE_SIZE / 2 - 6, YELLOW);
}