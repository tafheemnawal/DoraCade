#ifndef COIN_H
#define COIN_H

#include "player.h"
#include "pipe.h"

typedef struct
{
    float x;
    float y;
    float radius;
    int collected;

} Coin;

void InitCoin(Coin *coin, Pipe *pipe);
void UpdateCoin(Coin *coin, Pipe *pipe);
void DrawCoin(Coin *coin);
int CheckCoinCollision(Player *player, Coin *coin);

#endif