#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "pipe.h"

int CheckPipeCollision(Player *player, Pipe *pipe);
int CheckCeilingCollision(Player *player);
int CheckFloorCollision(Player *player, int screenHeight);

#endif