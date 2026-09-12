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
    
    pac->speed = 180.0f;
    pac->rotation = 0.0f;   
}

void LoadPacPlayerTexture(PacPlayer *pac)
{
    pac->texture = LoadTexture("../assets/textures/pacplayer.png");
}

void UnloadPacPlayerTexture(PacPlayer *pac)
{
    UnloadTexture(pac->texture);
}

void UpdatePacPlayer(PacPlayer *pac, float dt) {
    // 1. Store input whenever key is pressed
    if (IsKeyPressed(KEY_RIGHT)) { pac->dirRow = 0;  pac->dirCol = 1;  pac->rotation = 0.0f;   }
    if (IsKeyPressed(KEY_LEFT))  { pac->dirRow = 0;  pac->dirCol = -1; pac->rotation = 0.0f;   } 
    if (IsKeyPressed(KEY_UP))    { pac->dirRow = -1; pac->dirCol = 0;  pac->rotation = 270.0f; }
    if (IsKeyPressed(KEY_DOWN))  { pac->dirRow = 1;  pac->dirCol = 0;  pac->rotation = 90.0f;  }

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
    float tileCenterX = (int)(pac->x + TILE_SIZE / 2.0f);
    float tileCenterY = (int)(pac->y + TILE_SIZE / 2.0f);

    float desiredSize = TILE_SIZE * 1.2f;
    float halfDesired = desiredSize / 2.0f;

    float sourceX = 0.0f;
    float sourceWidth = (float)pac->texture.width;
    float sourceHeight = (float)pac->texture.height;

    // Flip horizontally when facing left
    if (pac->dirCol == -1)
    {
        sourceX = sourceWidth;
        sourceWidth = -sourceWidth;
    }

    Rectangle source = { sourceX, 0.0f, sourceWidth, sourceHeight };
    Rectangle dest = { tileCenterX, tileCenterY, desiredSize, desiredSize };
    Vector2 origin = { halfDesired, halfDesired };

    DrawTexturePro(pac->texture, source, dest, origin, pac->rotation, WHITE);
}