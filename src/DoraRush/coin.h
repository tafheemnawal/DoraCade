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
    Texture2D texture;

} Coin;

void InitCoin(Coin *coin, Pipe *pipe);
void LoadCoinTexture(Coin *coin);
void UpdateCoin(Coin *coin, Pipe *pipe);
void DrawCoin(Coin *coin);
int CheckCoinCollision(Player *player, Coin *coin);
void UnloadCoinTexture(Coin *coin);

#endif