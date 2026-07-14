#include "coin.h"
#include <raylib.h>

void InitCoin(Coin *coin, Pipe *pipe)
{
    coin->x = pipe->x + pipe->width / 2;
    coin->y = pipe->gapY + pipe->gapHeight / 2;
    coin->radius = 15;
    coin->collected = 0;
}

void UpdateCoin(Coin *coin, Pipe *pipe)
{
    // Coin stays centered in the pipe's gap, moving with it
    coin->x = pipe->x + pipe->width / 2;
    coin->y = pipe->gapY + pipe->gapHeight / 2;

    if (pipe->justRespawned)
    {
        coin->collected = 0;
    }
}

void DrawCoin(Coin *coin)
{
    if (!coin->collected)
    {
        DrawCircle(coin->x, coin->y, coin->radius, YELLOW);
    }
}