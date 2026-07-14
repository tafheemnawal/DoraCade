#ifndef PIPE_H
#define PIPE_H

#include "player.h"

typedef struct
{
    float x;
    float gapY;

    float width;
    float gapHeight;

    int scored;
    int justRespawned;

} Pipe;

void InitPipe(Pipe *pipe, int screenWidth);
void UpdatePipe(Pipe *pipe,int screenWidth, float dt);
void DrawPipe(Pipe *pipe, int screenHeight);

int CheckPipeCollision(Player *player, Pipe *pipe, int screenHeight);
int CheckPipeScore(Player *player, Pipe *pipe); 

#endif