#include "player.h"


void UpdatePlayer(Player *player, int screenWidth, int screenHeight, float dt)
{
    if (IsKeyDown(KEY_D))
    {
        player->x += player->speed * dt;
    }

    if (IsKeyDown(KEY_A))
    {
        player->x -= player->speed * dt;
    }

    if (IsKeyDown(KEY_W))
    {
        player->y -= player->speed * dt;
    }

    if (IsKeyDown(KEY_S))
    {
        player->y += player->speed * dt;
    }


    if (player->x < 0)
    {
        player->x = 0;
    }

    if (player->x > screenWidth - player->width)
    {
        player->x = screenWidth - player->width;
    }

    if (player->y < 0)
    {
        player->y = 0;
    }

    if (player->y > screenHeight - player->height)
    {
        player->y = screenHeight - player->height;
    }
}



void DrawPlayer(Player *player)
{
    DrawRectangle(
        player->x,
        player->y,
        player->width,
        player->height,
        player->color
    );
}



void InitPlayer(Player *player, int screenWidth, int screenHeight)
{
    player->width = 50;
    player->height = 50;

    player->speed = 300;
    player->color = BLUE;

    player->x = (screenWidth - player->width) / 2;
    player->y = (screenHeight - player->height) / 2;
}