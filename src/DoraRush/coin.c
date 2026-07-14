#include "coin.h"
#include <raylib.h>

void InitCoin(Coin *coin, Pipe *pipe)
{
    coin->x = pipe->x + pipe->width / 2;
    coin->y = pipe->gapY + pipe->gapHeight / 2;
    coin->radius = 22;
    coin->collected = 0;
}

void LoadCoinTexture(Coin *coin)
{
    coin->texture = LoadTexture("assets/textures/doracake.png");
}

void UnloadCoinTexture(Coin *coin)
{
    UnloadTexture(coin->texture);
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

int CheckCoinCollision(Player *player, Coin *coin)
{
    if (coin->collected)
    {
        return 0;
    }

    Rectangle playerRect =
    {
        player->x,
        player->y,
        player->width,
        player->height
    };

    Vector2 coinCenter = { coin->x, coin->y };

    if (CheckCollisionCircleRec(coinCenter, coin->radius, playerRect))
    {
        coin->collected = 1;
        return 1;
    }

    return 0;
}