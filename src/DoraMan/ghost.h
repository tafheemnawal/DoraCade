#ifndef GHOST_H
#define GHOST_H

#include <raylib.h>

typedef struct
{
    int row;
    int col;
    int targetRow;
    int targetCol;
    float x;
    float y;
    int dirRow;
    int dirCol;
    float speed;
    Texture2D texture;
} Ghost;

void InitGhost(Ghost *ghost, int startRow, int startCol);
void LoadGhostTexture(Ghost *ghost);
void UnloadGhostTexture(Ghost *ghost);
void UpdateGhost(Ghost *ghost, float dt);
void DrawGhost(Ghost *ghost);
int CheckGhostCollision(Ghost *ghost, float playerX, float playerY);

#endif