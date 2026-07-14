#include "collision.h"

int CheckPipeCollision(Player *player, Pipe *pipe)
{
    // Horizontal overlap
    if (player->x + player->width > pipe->x &&
        player->x < pipe->x + pipe->width)
    {
        // Top pipe collision
        if (player->y < pipe->gapY)
        {
            return 1;
        }

        // Bottom pipe collision
        if (player->y + player->height > pipe->gapY + pipe->gapHeight)
        {
            return 1;
        }
    }

    return 0;
}


int CheckCeilingCollision(Player *player)
{
    if (player->y < 0)
    {
        return 1;
    }

    return 0;
}


int CheckFloorCollision(Player *player, int screenHeight)
{
    if (player->y + player->height > screenHeight)
    {
        return 1;
    }

    return 0;
}