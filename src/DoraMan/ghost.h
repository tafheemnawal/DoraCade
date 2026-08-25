#ifndef GHOST_H
#define GHOST_H

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
} Ghost;

void InitGhost(Ghost *ghost, int startRow, int startCol);
void UpdateGhost(Ghost *ghost, float dt);
void DrawGhost(Ghost *ghost);

#endif